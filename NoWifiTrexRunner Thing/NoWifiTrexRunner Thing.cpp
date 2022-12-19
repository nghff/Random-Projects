//http://www.trex-game.skipser.com/

#include <Windows.h>
#include <iostream>

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

int PosR(int x, int y)
{
    return ScreenData[4 * ((y * ScreenX) + x) + 2];
}

int main()
{
    POINT cPos1;
    while (!GetAsyncKeyState(VK_RETURN))
    {
        Sleep(100);
    }
    GetCursorPos(&cPos1);
    std::cout << "Cactus coords set" << std::endl;
    POINT cPos2;
    while (GetAsyncKeyState(VK_RETURN))
    {
        Sleep(100);
    }
    while (!GetAsyncKeyState(VK_RETURN))
    {
        Sleep(100);
    }
    GetCursorPos(&cPos2);
    std::cout << "Bird coords set" << std::endl;
    float off = 0;
    while (true)
    {
        if (GetAsyncKeyState(VK_CONTROL))
        {
            off += 0.01f;
            ScreenCap();
            for (int i = 16; i <= 56; i += 4)
            {
                if (PosR(cPos1.x + int(off * 0.8f) + i, cPos1.y) == 83) 
                {
                    keybd_event(VK_UP, 0, 0, 0);
                }
            }
            for (int i = 0; i <= 4; i+= 2) 
            {
                if (PosR(cPos2.x + int(off * 1.1f) + (i/3), cPos2.y) == 83) 
                {
                    keybd_event(VK_DOWN, 0, 0, 0);
                    Sleep(125);
                    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
                }
            }
        }
    }
}