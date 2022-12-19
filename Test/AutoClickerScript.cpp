#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

void AutoL(double cps) 
{
    SHORT mkey = VK_RSHIFT;
    SHORT ckey = VkKeyScan('c');
    float t = 1000 / cps;
    while (1) 
    {
        if (GetAsyncKeyState(mkey))
        {
            while (GetAsyncKeyState(mkey)) 
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(t);
            }
            while (!GetAsyncKeyState(mkey))
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(t);
            }
            while (GetAsyncKeyState(mkey)) 
            {
                Sleep(30);
            }
        }
        if (GetAsyncKeyState(ckey))
        {
            return;
        }
        Sleep(30);
    }
}

void AutoR(double cps)
{
    SHORT mkey = VK_MBUTTON;
    SHORT ckey = VkKeyScan('c');
    float t = 1000 / cps;
    while (1) {
        if (GetAsyncKeyState(mkey))
        {
            while (GetAsyncKeyState(mkey)) 
            {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                Sleep(t);
            }
            while (!GetAsyncKeyState(mkey))
            {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                Sleep(t);
            }
            while (GetAsyncKeyState(mkey)) 
            {
                Sleep(30);
            }
        }
        if (GetAsyncKeyState(ckey))
        {
            return;
        }
        Sleep(30);
    }
}


int main()
{
    double cps;
    char LR;
    while (1) {
        cout << "cps (<cps> <L/R>): ";
        cin >> cps >> LR;
        if (cps > 300) cout << "Uh oh... that might crash the computer. Try Again:)" << endl;
        else break;
    }
    HWND cswindow = GetConsoleWindow();
    FreeConsole();
    SendMessage(cswindow, WM_CLOSE, 0, 0);
    HANDLE proc = GetCurrentProcess();
    SetPriorityClass(proc, PROCESS_MODE_BACKGROUND_BEGIN);
    if (LR == 'L') AutoL(cps);
    else AutoR(cps);
}