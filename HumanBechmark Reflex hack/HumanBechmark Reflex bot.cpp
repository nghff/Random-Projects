//https://humanbenchmark.com/tests/reactiontime

#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
	POINT cPos; 
	while (!GetAsyncKeyState(VK_RETURN))
	{
		Sleep(100);
	}
	cout << "SetCursor" << endl << endl;
	GetCursorPos(&cPos);
	HDC dc = GetDC(NULL);
	while (1)
	{
		if (GetGValue(GetPixel(dc, cPos.x, cPos.y)) == 219)
		{
			cout << "Clicking" << endl;
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(200);
		}
	}
}