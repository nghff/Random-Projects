//https://www.silvergames.com/en/piano-tiles
// OR:
//https://www.agame.com/game/magic-piano-tiles
#include <iostream>
#include <Windows.h>
bool ButtonPress(int Key)
{
	bool button_pressed = false;

	while (GetAsyncKeyState(Key))
		button_pressed = true;

	return button_pressed;
}
int main()
{
	POINT pt1, pt2, pt3, pt4;
	HDC hdc = GetDC(NULL);
	float offset = 0;
	while (1) {
		if (ButtonPress(VK_SPACE)) {
			GetCursorPos(&pt1);
			std::cout << "point 1 selected...\n";
			break;
		}
	}
	while (1) {
		if (ButtonPress(VK_SPACE)) {
			GetCursorPos(&pt2);
			std::cout << "point 2 selected...\n";
			break;
		}
	}
	while (1) {
		if (ButtonPress(VK_SPACE)) {
			GetCursorPos(&pt3);
			std::cout << "point 3 selected...\n";
			break;
		}
	}
	while (1) {
		if (ButtonPress(VK_SPACE)) {
			GetCursorPos(&pt4);
			std::cout << "point 4 selected\nRUNNING...";
			break;
		}
	}
	const int x1 = pt1.x, y1 = pt1.y, x2 = pt2.x, x3 = pt3.x, x4 = pt4.x;
	INPUT mouseD = { 0 };
	mouseD.type = INPUT_MOUSE;
	mouseD.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	const int sizeofmouseclick = sizeof(INPUT);
	while (1) {
		while (GetAsyncKeyState(VK_SPACE)) {

			offset += 0.05f;//adjust this value for different songs.
			if (GetRValue(GetPixel(hdc, x1, y1)) <= 20) {
				SetCursorPos(x1, y1 + offset);
				SendInput(1, &mouseD, sizeofmouseclick);
			}
			else if (GetRValue(GetPixel(hdc, x2, y1)) <= 20) {
				SetCursorPos(x2, y1 + offset);
				SendInput(1, &mouseD, sizeofmouseclick);
			}
			else if (GetRValue(GetPixel(hdc, x3, y1)) <= 20) {
				SetCursorPos(x3, y1 + offset);
				SendInput(1, &mouseD, sizeofmouseclick);
			}
			else if (GetRValue(GetPixel(hdc, x4, y1)) <= 20) {
				SetCursorPos(x4, y1 + offset);
				SendInput(1, &mouseD, sizeofmouseclick);
			}
		}

		offset = 0;
	}
}
