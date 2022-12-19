#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
int main()
{
	HWND deskWind = GetDesktopWindow(), cswindow = GetConsoleWindow();
	FreeConsole();
	SendMessage(cswindow, WM_CLOSE, 0, 0);
	MessageBox(
		deskWind, 
		L"Welcome to Nathan's Zoom Chat Spammer.\n Hotkey: Esc\nTo stop the program, use: Ctrl + Shift + Q", 
		L"Zoom Chat Spammer", 
		MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1
	);
	HANDLE proc = GetCurrentProcess();
	SetPriorityClass(proc, PROCESS_MODE_BACKGROUND_BEGIN);
	SHORT letters[26];
	for (int i = 65; i < 91; i++)
	{
		letters[i - 65] = VkKeyScan(char(i));
	}
	int i = 0;
	while (true)
	{
		while (GetAsyncKeyState(VK_ESCAPE))
		{
			keybd_event(letters[i], 0, 0, 0);
			keybd_event(letters[i], 0, 0x0002, 0);
			Sleep(2);
			keybd_event(0x0D, 0, 0, 0);
			keybd_event(0x0D, 0, 0x0002, 0);
			Sleep(1);
			i++;
			if (i == 26)
			{
				i = 0;
			}
		}
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState('Q'))
		{
			MessageBox(
				deskWind, 
				L"Program closed.", 
				L"Zoom Chat Spammer", 
				MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1
			);
			CloseHandle(proc);
			return 0;
		}
		Sleep(50);
	}
	return 0;
}