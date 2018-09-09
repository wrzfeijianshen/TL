#include <windows.h>
#include <tchar.h>
#include "Raster.h"

LRESULT CALLBACK    windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return  DefWindowProc(hWnd, msg, wParam, lParam);
}

int     WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//  1 注册窗口类
	::WNDCLASSEXA winClass;
	winClass.lpszClassName = "Raster";
	winClass.cbSize = sizeof(::WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	winClass.lpfnWndProc = windowProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = 0;
	winClass.hIconSm = 0;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)(BLACK_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	RegisterClassExA(&winClass);

	//  2 创建窗口
	HWND    hWnd = CreateWindowEx(
		NULL,
		_T("Raster"),
		_T("Raster"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0,
		0,
		256,
		256,
		0,
		0,
		hInstance,
		0
	);

	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);

	RECT rt = { 0 };
	GetClientRect(hWnd, &rt);// 得到客户区
	int width = rt.right - rt.left;
	int height = rt.bottom - rt.top;
	void *buffer = 0;
	HDC hDC = GetDC(hWnd);
	HDC hMem = ::CreateCompatibleDC(hDC);

	// 一副图片
	BITMAPINFO	bmpInfor;
	bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfor.bmiHeader.biWidth = width;
	bmpInfor.bmiHeader.biHeight = -height;
	bmpInfor.bmiHeader.biPlanes = 1;
	bmpInfor.bmiHeader.biBitCount = 32;// 比特位
	bmpInfor.bmiHeader.biCompression = BI_RGB;
	bmpInfor.bmiHeader.biSizeImage = 0;
	bmpInfor.bmiHeader.biXPelsPerMeter = 0;
	bmpInfor.bmiHeader.biYPelsPerMeter = 0;
	bmpInfor.bmiHeader.biClrUsed = 0;
	bmpInfor.bmiHeader.biClrImportant = 0;

	// 创建位图
	HBITMAP	hBmp = CreateDIBSection(hDC, &bmpInfor, DIB_RGB_COLORS, (void**)&buffer, 0, 0);
	SelectObject(hMem, hBmp);// dc相当于画板，hbmp相当于值，把值复制给画板
	CELL::Raster    raster(width,height, buffer);

	MSG     msg = { 0 };
	while (true)
	{
		if (msg.message == WM_DESTROY || msg.message == WM_CLOSE || msg.message == WM_QUIT)
		{
			break;
		}
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 画图
		raster.clear();
		CELL::float2    points[] =
		{
			CELL::float2(50,50),
			CELL::float2(200,50),
			CELL::float2(33,88),
			CELL::float2(159,100),
		};

		CELL::float2 prev[2];
		for (float t = 0; t < 1.0f; t += 0.01f)
		{
			float x = points[0].x * pow(1 - t, 3)
				+ 3 * points[1].x * t * pow(1 - t, 2)
				+ 3 * points[2].x * t*t * (1 - t)
				+ points[3].x * t * t * t;
			float y = points[0].y * pow(1 - t, 3)
				+ 3 * points[1].y * t * pow(1 - t, 2)
				+ 3 * points[2].y * t*t * (1 - t)
				+ points[3].y * t * t * t;
			if (t == 0)
			{
				prev[0] = CELL::float2(x, y);
			}
			else
			{
				prev[1] = CELL::float2(x, y);
				raster.drawArrays(CELL::DM_LINES, prev, 2);
				prev[0] = prev[1];
			}
		}
		raster.drawFilleRect(60, 100, 80, 80);
		raster.drawFilleRect(-10, -10, 30, 30);
		raster.drawFilleRect(150, 150, 200, 200);
		CELL::int2  pt[] =
		{
			CELL::int2(10,10),
			CELL::int2(110,10),
			CELL::int2(110,110),
			CELL::int2(10,110),
		};

		CELL::Rgba  colors[] =
		{
			CELL::Rgba(255,0,0),
			CELL::Rgba(0,255,0),
			CELL::Rgba(0,0,255),
			CELL::Rgba(0,0,0),
			//CELL::Rgba(255,255,255),

		};

		raster.drawRect(pt, colors);

		memcpy(buffer, raster._buffer, width*raster._height*sizeof(CELL::Rgba));
		BitBlt(hDC, 0, 0, width, height, hMem, 0, 0, SRCCOPY);
	}

	return  0;
}