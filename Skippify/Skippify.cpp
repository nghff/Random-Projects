#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <tlhelp32.h>
using namespace std;

void unpause(HWND handle)
{
    Sleep(100);
    HWND skippify = FindWindow(NULL, L"Spotify");

    SetForegroundWindow(skippify);

    Sleep(300);
    keybd_event(VK_SPACE, 0, 0, 0);
    Sleep(10);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
    Sleep(300);

    SetForegroundWindow(handle);
}

bool ButtonPress(int Key)
{
    bool button_pressed = false;

    while (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState(Key))
        button_pressed = true;

    return button_pressed;
}

bool IsProcessRunning(const wchar_t* processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
        while (Process32Next(snapshot, &entry))
            if (!_wcsicmp(entry.szExeFile, processName))
                exists = true;

    CloseHandle(snapshot);
    return exists;
}

int main()
{

    cout << IsProcessRunning(L"Spotify.exe");
    HWND last = GetForegroundWindow();;
    ShellExecute(NULL, L"open", L"C:\\Users\\natha\\AppData\\Roaming\\Spotify\\Spotify.exe", NULL, NULL, SW_SHOW);
    unpause(last);
    
    //HWND cswindow = GetConsoleWindow();
    //FreeConsole();
    //SendMessage(cswindow, WM_CLOSE, 0, 0);
    short sk = VkKeyScan('1');
    cout << IsProcessRunning(L"Spotify.exe") << '\n';
    int i = 0;
    while (1)
    {
        Sleep(75);
        if (i == 150)
            if (!IsProcessRunning(L"Spotify.exe")) return 0;
            else i = 0;
        if (ButtonPress(sk))
        {
            cout << '\n';
            last = GetForegroundWindow();
            system("taskkill /IM Spotify.exe /F");
            ShellExecute(NULL, L"open", L"C:\\Users\\natha\\AppData\\Roaming\\Spotify\\Spotify.exe", NULL, NULL, SW_SHOW);
            cout << GetLastError();
            Sleep(2500);
            unpause(last);
        }
        i++;
    }
}