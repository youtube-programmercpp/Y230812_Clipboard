#include <Windows.h>
#include <string.h>
// Ctrl+C キーを押したときの処理


HGLOBAL GlobalAllocCopy(LPCVOID pvSrc, SIZE_T cbSrc)
{
	//メモリを用意する
	const HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbSrc);
	if (hMem == NULL)
		return NULL;
	else {
		//メモリにサンプルデータをコピー
		const LPVOID pvMem = GlobalLock(hMem);
		if (pvMem == NULL) {
			GlobalFree(hMem);
			return NULL;
		}
		else {
			CopyMemory(pvMem, pvSrc, cbSrc);
			GlobalUnlock(hMem);
			return hMem;
		}
	}
}
int main()
{
	static const char sample_data[] = "TEST";
	const HGLOBAL hMem = GlobalAllocCopy(sample_data, sizeof sample_data);
	if (hMem != NULL) {
		if (OpenClipboard(NULL)) {
			//まず、クリップボードの内容をすべて破棄する
			EmptyClipboard();
			if (!SetClipboardData(CF_TEXT, hMem))
				GlobalFree(hMem);
			CloseClipboard();
		}
	}
}
