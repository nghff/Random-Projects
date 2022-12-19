#include <Windows.h>

using namespace std;
//hint funcs
void CheckKeybinds();
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

void CloseApplications()
{
	EnumWindows(EnumWindowsProc, NULL);
	return;
}

int main()
{
	while (1)
	{
		Sleep(500);
		CheckKeybinds();
	}
}

void CheckKeybinds()
{
	HWND cswnd = GetConsoleWindow();
	FreeConsole();
	SendMessage(cswnd, WM_CLOSE, 0, 0);
	if (GetAsyncKeyState(VK_CONTROL))
	{
		if (GetAsyncKeyState(VK_MENU))
		{
			if (GetAsyncKeyState('Z'))
			{
				CloseApplications();
			}
		}
	}
	return;
}

//enums

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if(IsWindowVisible(hWnd))
		SendMessage(hWnd, WM_DESTROY, 0, 0);
	return TRUE;
}