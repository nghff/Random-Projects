#include <windows.h>
#include <vector>
#include <algorithm>
#include <ranges>
#include <execution>
#include <numeric>
#include <iostream>
using namespace std;

int ScreenX = 0;
int ScreenY = 0;
BYTE* ScreenData = 0;
HDC hScreen = GetDC(NULL);
HDC hdcMem = CreateCompatibleDC(hScreen);

void ScreenCap()
{
    ScreenX = GetDeviceCaps(hScreen, HORZRES);
    ScreenY = GetDeviceCaps(hScreen, VERTRES);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, ScreenX, ScreenY);
    HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, ScreenX, ScreenY, hScreen, 0, 0, SRCCOPY);
    SelectObject(hdcMem, hOld);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = ScreenX;
    bmi.biHeight = -ScreenY;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;// 3 * ScreenX * ScreenY;

    if (ScreenData)
        free(ScreenData);
    ScreenData = (BYTE*)malloc(4 * ScreenX * ScreenY);

    GetDIBits(hdcMem, hBitmap, 0, ScreenY, ScreenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
    DeleteObject(hBitmap);
}

int f(int x, int y)
{
    if (x % 2 == 0) return f(x / 2, y - 3) - x * y;
    if (x % 2 != 0 && x % 3 == 0) return f(y + 2, x / 3) + x;
    return x * y;
}

int main()
{
    cout << f(12, 18) << '\n';
}