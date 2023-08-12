#include <iostream>
#include <Windows.h>
//クリップボードに設定されているデータは複数あるのが普通
//テキストの場合は ANSI文字列（シフトJIS文字列の意味）とUNICODE文字列の２本立て
void f1()
{
	if (const auto hMem = GetClipboardData(CF_TEXT)) {
		if (const auto pvMem = GlobalLock(hMem)) {
			MessageBoxA(nullptr, LPCSTR(pvMem), "ANSI文字列", 0);
			GlobalUnlock(hMem);
		}
	}
}
void f2()
{
	if (const auto hMem = GetClipboardData(CF_UNICODETEXT)) {
		if (const auto pvMem = GlobalLock(hMem)) {
			MessageBoxW(nullptr, LPCWSTR(pvMem), L"UNICODE文字列", 0);
			GlobalUnlock(hMem);
		}
	}
}
int main()
{
	if (OpenClipboard(nullptr)) {
		f1();
		f2();
		CloseClipboard();
	}
}
