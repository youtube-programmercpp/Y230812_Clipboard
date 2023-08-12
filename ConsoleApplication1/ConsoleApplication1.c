#include <Windows.h>
#include <stdio.h>

//クリップボード内の文字列を puts で出力するサンプル（C言語）

int main()
{
	// Ctrl+V キーが押された時の処理

	//まず OpenClipboard を呼ぶ
	if (OpenClipboard(NULL)) {
		const HGLOBAL hMem = GetClipboardData(/*取得したいデータの種類を指定する*/CF_TEXT);
		if (hMem != NULL) {
			//メモリ内容へのアクセスに先だってロックする
			const LPCVOID pvMem = GlobalLock(hMem);
			if (pvMem != NULL) {
				puts((const char*)pvMem);
				//メモリ内容へのアクセスが済んだらアンロックする
				GlobalUnlock(hMem);
			}
		}
		CloseClipboard();
	}
}
