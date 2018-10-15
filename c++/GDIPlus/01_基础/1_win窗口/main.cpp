#include <windows.h>
#include<stdlib.h>
#include <gdiplus.h>
#include<tchar.h>

using namespace Gdiplus;

#pragma comment(lib, "GdiPlus.lib")

int width, height;

void OnDraw(HDC hdc)
{
	WCHAR buf[128];
	int len;
	len = wsprintfW(buf, L"width:%d height:%d\n", width, height);

	SolidBrush b(Color(255, 100, 200, 150));
	HBITMAP bg = CreateCompatibleBitmap(hdc, width, height);
	HDC memdc = CreateCompatibleDC(hdc);
	SelectObject(memdc, bg);

	FontFamily fm(L"Consolas");
	Font f(&fm, 12, 2, UnitPoint);

	Graphics mg(memdc);
	mg.SetSmoothingMode(SmoothingModeHighQuality);
	mg.Clear(Color(255, 128, 128, 128));

	mg.DrawString(buf, len, &f, PointF(0.0, 0.0), &b);

	if (!BitBlt(hdc, 0, 0, width, height, memdc, 0, 0, SRCCOPY))
		MessageBox(NULL, L"BitBlt failed!", L"warning", MB_ICONWARNING);

	DeleteObject(bg);
	DeleteDC(memdc);
}

void OnLButtonDown(HWND hwnd, int x, int y)
{

	InvalidateRect(hwnd, NULL, FALSE);
}

void OnLButtonUp(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, FALSE);
}

void OnMouseMove(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, FALSE);
}

void OnSize(HWND hwnd, int w, int h)
{
	width = w;
	height = h;
	InvalidateRect(hwnd, NULL, FALSE);
}

void OnCreate(HWND hwnd)
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_CREATE:
		OnCreate(hwnd);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		OnDraw(ps.hdc);
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		OnLButtonDown(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_LBUTTONUP:
	{
		OnLButtonUp(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		OnMouseMove(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_SIZE:
	{
		OnSize(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszClassName = L"windows";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	width = 640;
	height = 480;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"windows", L"GDI+ [feijianshen]", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ULONG_PTR token;
	GdiplusStartupInput gdipinput;
	GdiplusStartup(&token, &gdipinput, NULL);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(token);
	return msg.wParam;
}
