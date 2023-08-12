// C言語サンプルプログラム Copyright(C) 2023 https://www.youtube.com/@ProgrammerCpp
#include <Windows.h>
#include <stdio.h>
#include <math.h>

//クリップボード内のデータに対して sscanf_s を実行する
int clipboard_sscanf_s(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int retval_vsscanf_s = 0;
	const HGLOBAL hMem = GetClipboardData(CF_TEXT);
	if (hMem) {
		const LPCVOID pvMem = GlobalLock(hMem);
		if (pvMem) {
			retval_vsscanf_s = vsscanf_s((LPCSTR)pvMem, format, args);
			(void)GlobalUnlock(hMem);
		}
	}
	va_end(args);
	return retval_vsscanf_s;
}

//クリップボード内のデータに対して sprintf_s を実行する
int clipboard_sprintf_s(const char* format, ...)
{
	BOOL succeeded = FALSE;
	va_list args;
	va_start(args, format);
	char buf[256];
	int retval_vsprintf_s = vsprintf_s(buf, sizeof buf, format, args);
	if (retval_vsprintf_s > 0) {
		const SIZE_T cbData = (unsigned)retval_vsprintf_s + (SIZE_T)1;
		const HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbData);
		if (hMem) {
			const LPVOID pvMem = GlobalLock(hMem);
			if (pvMem) {
				memcpy(pvMem, buf, cbData);
				GlobalUnlock(hMem);

				if (EmptyClipboard()) {
					if (SetClipboardData(CF_TEXT, hMem))
						succeeded = TRUE;
				}
			}
			if (!succeeded)
				GlobalFree(hMem);
		}
	}
	va_end(args);
	return succeeded ? retval_vsprintf_s : 0;
}

//クリップボード内のデータに対して四捨五入を実施する
BOOL clipboard_round_off()
{
	BOOL succeeded = FALSE;
	if (OpenClipboard(NULL)) {
		double org_value;
		if (clipboard_sscanf_s("%lf", &org_value) == 1) {
			//四捨五入
			printf("処理前の値は %f です。\n", org_value);
			double new_value = floor(fabs(org_value) + .5);
			if (org_value < 0)
				new_value *= -1;
			printf("処理後の値は %f です。\n", new_value);
			succeeded = clipboard_sprintf_s("%.0f", new_value);
		}
		(void)CloseClipboard();
	}
	return succeeded;
}

int main()
{
	printf("クリップボード内のデータを四捨五入します。\n");
	if (clipboard_round_off())
		printf("処理は成功しました。メモ帳などで Ctrl+V のキー操作を行うことで結果を確かめることが出来ます。\n");
	else
		printf("処理は失敗しました。\n");
}
/*
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q14284303924
sin********さん

2023/8/11 22:10

『Ctrl + C』でコピーした文字列は、PC内部のどこに保存されるのでしょうか？
またそのコピーした文字列はｃ言語プログラムの文中で呼び出し可能でしょうか？
「コピーした文字列（半角の数列）を四捨五入する」というプログラムをｃ言語またはJavaで作りたいと考えてます。

C言語関連 | Java・84閲覧・100
*/
