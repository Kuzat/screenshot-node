#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <stdlib.h>
#include <iostream>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}


void getScreen(const int x, const int y, int W, int H, const char* path) {
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	{
		// get the height and width of the screen
		SetProcessDPIAware();

		if (W == 0) {
			W = GetSystemMetrics(SM_CXSCREEN);
		}
		if (H == 0) {
			H = GetSystemMetrics(SM_CYSCREEN);
		}

		HDC hdc = GetDC(NULL); // get the desktop device context
		HDC hDest = CreateCompatibleDC(hdc); // create a device context to use yourself

		// create a bitmap
		HBITMAP hbDesktop = CreateCompatibleBitmap(hdc, W, H);

		// use the previously created device context with the bitmap
		SelectObject(hDest, hbDesktop);

		// copy from the desktop device context to the bitmap device context
		BitBlt(hDest, x, y, W, H, hdc, 0, 0, SRCCOPY);

		Bitmap bitmap(hbDesktop, NULL);
		CLSID clsid;
		size_t size = strlen(path) + 1;
		wchar_t* pathName = new wchar_t[size];
		size_t outSize;
		mbstowcs_s(&outSize, pathName, size, path, size - 1);
		GetEncoderClsid(L"image/png", &clsid);
		bitmap.Save(pathName, &clsid, NULL);


		// after the recording is done, release the desktop context you got..
		ReleaseDC(NULL, hdc);
		DeleteObject(hbDesktop);

		// ..and delete the context you created
		DeleteDC(hDest);
	}

	GdiplusShutdown(gdiplusToken);
}
