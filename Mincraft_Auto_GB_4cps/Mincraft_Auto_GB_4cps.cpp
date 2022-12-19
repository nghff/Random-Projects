#include <iostream>
#include <Windows.h>
using namespace std;

bool ButtonPress(int Key)
{
	bool button_pressed = false;

	while (GetAsyncKeyState(Key))
		button_pressed = true;

	return button_pressed;
}

int main()
{

	int max = 333;
	int min = 166;
	const SHORT fK = VkKeyScan('f');
	const SHORT aK = VkKeyScan('a'), sK = VkKeyScan('s');
	const SHORT fasterK = VkKeyScan('g'), slowerK = VkKeyScan('h');
	const SHORT exitK = VkKeyScan('p');
	while (1)
	{
		if (GetAsyncKeyState(fK))
		{
			const int mid = (max + min) / 2;
			cout << "Running Inverval: " << mid << endl << endl;
			keybd_event(aK, 0, 0, 0);
			keybd_event(sK, 0, 0, 0);
			keybd_event(0x10, 0, 0x0002, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			Sleep(mid * 5 / 4);
			while (GetAsyncKeyState(fK))
			{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				Sleep(mid);
			}
			Sleep(50);
		}
		if (ButtonPress(fasterK))
		{
			if (max - min != 0) max = (max + min) / 2;
			else
			{
				max--; min--;
			}
			cout << "Updated Interval: " << (max + min) / 2 << endl << endl;
		}
		if (ButtonPress(slowerK))
		{
			if (max - min != 0) min = (max + min) / 2;
			else
			{
				max++; min++;
			}
			cout << "Updated Interval: " << (max + min) / 2 << endl << endl;
		}
		if (GetAsyncKeyState(exitK))
			break;
		Sleep(50);
	}
	HWND cswindow = GetConsoleWindow();
	FreeConsole();
	SendMessage(cswindow, WM_CLOSE, 0, 0);
}