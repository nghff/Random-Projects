#ifndef UNICODE
#define UNICODE
#endif 
#include <Windows.h>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <thread>
using namespace std;
HWND hwnd;
PAINTSTRUCT ps;
HDC hdc;
RECT rcClientRect;
bool running = true;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void FrameManager()
{
    while (running)
    {
        Sleep(2);
        InvalidateRect(hwnd, &ps.rcPaint, false);
    }
}
struct Vector2
{
    int x, y;
    Vector2& operator+(const Vector2& other)
    {
        Vector2 result = { x + other.x, y + other.y };
        return result;
    }
};
Vector2 newVector2(int x, int y)
{
    Vector2 newVec;
    newVec.x = x;
    newVec.y = y;
    return newVec;
}
class rectObject
{
public:
    int width = 0;
    int height = 0;
    RECT RectInfo = { 0, 0, 0, 0 };
    Vector2 position = newVector2(0, 0);
    Vector2 Velecity = newVector2(0, 0);
    COLORREF color = RGB(0, 0, 0);
    bool active = false;
    string tag = "untagged";
    void setPosition(Vector2 newPos)
    {
        if (active)
            return;
        this->position = newPos;
        this->RectInfo.left = newPos.x;
        this->RectInfo.right = this->RectInfo.left + width;
        this->RectInfo.top = newPos.y;
        this->RectInfo.bottom = this->RectInfo.top + height;
    }
};
struct textObject
{
    string text = "New Text";
    Vector2 position = newVector2(0, 0);
    COLORREF TextColor = RGB(255, 255, 255);
    int size = 20;
};
textObject* newTextObject(string text, Vector2 position, COLORREF TextColor, int size)
{
    textObject* newtxt = new textObject();
    newtxt->text = text;
    newtxt->position = position;
    newtxt->TextColor = TextColor;
    newtxt->size = size;
    return newtxt;
}

//Game variables
HBRUSH bkRoundBrush = CreateSolidBrush(RGB(30, 30, 30));
rectObject Player;
vector<rectObject*> objects;
vector<textObject*> textObjects;

//Game functions
bool isColliding(RECT r1, RECT r2)
{
    if (r1.left >= r2.right || r2.left >= r1.right)
        return false;

    if (r1.top >= r2.bottom || r2.top >= r1.bottom)
        return false;

    return true;
}

//Happens on starting game once
void Start()
{

}

//"Calculatons" for each frame
void Update()
{

}

//Paints the frame to the window
void Render()
{
    //MAGIC yay
    HDC memDC = CreateCompatibleDC(ps.hdc);


    HBITMAP bmp = CreateCompatibleBitmap(ps.hdc,
        rcClientRect.right - rcClientRect.left,
        rcClientRect.bottom - rcClientRect.top);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

    //Draw the stuffs
    FillRect(memDC, &ps.rcPaint, bkRoundBrush);
    for (rectObject* i : objects)
    {
        if (!i->active)
        {
            HBRUSH brush = CreateSolidBrush(i->color);
            SelectObject(memDC, brush);
            i->setPosition(i->position + i->Velecity);
            Rectangle(memDC, i->RectInfo.left, i->RectInfo.top, i->RectInfo.right, i->RectInfo.bottom);
            DeleteObject(brush);
        }
    }

    SetBkMode(memDC, 1);
    int id = 0;
    for (textObject* i : textObjects)
    {
        HFONT hFont, hTmp;
        hFont = CreateFont(i->size, 0, 0, 0, 700, 0, 0, 0, 0, 5, 5, 5, 0, L"SYSTEM_FIXED_FONT");
        hTmp = (HFONT)SelectObject(memDC, hFont);
        SetTextColor(memDC, i->TextColor);
        TextOutA(memDC, i->position.x, i->position.y, i->text.c_str(), i->text.length());
        DeleteObject(SelectObject(memDC, hTmp));
        DeleteObject(hFont);
        id++;
    }




    //Display the stuffs
    BitBlt(hdc, 0, 0, rcClientRect.right - rcClientRect.left,
        rcClientRect.bottom - rcClientRect.top, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBmp);
    DeleteObject(bmp);
    DeleteDC(memDC);

}

//The main func
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    Start();
    const wchar_t CLASS_NAME[] = L"Game";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);


    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Game",
        (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) ^ WS_MAXIMIZEBOX,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    thread fm(FrameManager);
    GetClientRect(hwnd, &rcClientRect);
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    DeleteObject(&ps);
    DeleteObject(bkRoundBrush);
    fm.join();
    return 0;
}

//A kind of "message handler"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        running = false;
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        Update();
        Render();
        EndPaint(hwnd, &ps);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}