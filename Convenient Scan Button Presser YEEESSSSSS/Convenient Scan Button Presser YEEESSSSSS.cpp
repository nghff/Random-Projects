#include <iostream>
#include <Windows.h>
using namespace std;

bool ButtonPress()
{
	bool button_pressed = false;

	while (GetAsyncKeyState(VK_CONTROL))
		button_pressed = true;

	return button_pressed;
}

bool ButtonPress2()
{
	bool button_pressed = false;

	while ((GetKeyState(VK_MBUTTON) & 0x100) != 0)
		button_pressed = true;

	return button_pressed;
}

int main()
{
	POINT pt1, pt2, pt3;
	HDC hdc = GetDC(NULL);
	float offset = 0;
	int x, y, a, b, z, w, i, j;
	while (1) {
		if (ButtonPress()) {
			GetCursorPos(&pt1);
			std::cout << "point 1 selected...\n";
			break;
		}
	}
	while (1) {
		if (ButtonPress()) {
			GetCursorPos(&pt2);
			std::cout << "point 2 selected...\n";
			break;
		}
	}
	while (1) {
		if (ButtonPress()) {
			GetCursorPos(&pt3);
			std::cout << "point 3 selected...\nRUNNING:)\n:):)\n:))\n:)";
			break;
		}
	}
	while (1)
	{
		if (ButtonPress2())
		{
			SetCursorPos(pt1.x, pt1.y);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(1000);
			SetCursorPos(pt2.x, pt2.y);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(3500);
			SetCursorPos(pt3.x, pt3.y);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(5000);
		}
		if (GetAsyncKeyState(VK_RBUTTON)) break;
	}
	cout << "SUCCESS!";
	return 0;
}