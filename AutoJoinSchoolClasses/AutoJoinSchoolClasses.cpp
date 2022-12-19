#include <Windows.h>
#include <iostream>
#include <string>
#include <shellapi.h>
#include <time.h>

using namespace std;

void toClipboard(const string& s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main()
{
	//HWND deskWind = GetDesktopWindow(), cswindow = GetConsoleWindow();
	//FreeConsole();
	//SendMessage(cswindow, WM_CLOSE, 0, 0);
	//MessageBox(
	//	deskWind,
	//	L"Auto Join Classes Enabled",
	//	L"Auto Join",
	//	MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1
	//);



	while (1)
	{
		time_t theTime = time(NULL);
		struct tm aTime;
		localtime_s(&aTime ,&theTime);
		int hr = aTime.tm_hour, min = aTime.tm_min;
		cout << "checking " << hr << ':' << min << "..." << endl;
		switch (hr)
		{
		case 8:
			if(min == 34)
			{
				ShellExecute(0, 0, L"https://zoom.us/j/5122820181", 0, 0, SW_SHOW);
				toClipboard("math");
			}
			break;
		case 9:
			if (min == 29)
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/96533499873?pwd=V0ovUFpXTVZJS0dYcVlTK1FnL0h6QT09", 0, 0, SW_SHOW);
			break;
		case 10:
			if (min == 24)
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/97224826344?pwd=Z1FRYlZFVS9WSElhWTJraHZ2OWZIZz09", 0, 0, SW_SHOW);
			break;
		case 11:
			if (min == 19)
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/88286680251?pwd=ZWo0UUp3eFVtbHN2Q3l1TW1kMktmdz09", 0, 0, SW_SHOW);
			break;
		case 12:
			if (min == 14)
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/96272156155?pwd=eXlDTmcrM0VrNjhKcVRLODNUSG53dz09", 0, 0, SW_SHOW);
			break;
		case 13:
			if (min == 39)
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/94114858434?pwd=RTJ2Y0Y1cEt4VnpydjVvcDRJc29oQT09", 0, 0, SW_SHOW);
			break;
		case 14:
			if (min == 7)
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/92404562946?pwd=cEoxM1gyZUxtS255Q1dsK0VpMS9QQT09", 0, 0, SW_SHOW);
			break;
		case 15:
			if (min == 2)
			{
				ShellExecute(0, 0, L"https://eanesisd.zoom.us/j/98245556112", 0, 0, SW_SHOW);
				toClipboard("948875");
				Sleep(5000);
				return 0;
			}
			break;
		}

		Sleep(40000);
	}

	//ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOW);
	//https://eanesisd.zoom.us/j/98090140195?pwd=UHpNcXVpY203M1RiaFp1ejZoc1Zudz09#success math count club
}