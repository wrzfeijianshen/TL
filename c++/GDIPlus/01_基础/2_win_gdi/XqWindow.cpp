#include "XqWindow.h"
#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment(lib, "GdiPlus.lib")

int width, height;
ULONG_PTR token;

CXqWindow::CXqWindow(HINSTANCE hInst)
	:m_HWnd(NULL),
	m_HInstance(hInst),
	m_IPosX(0),
	m_IPosY(0),
	m_IWidth(300),
	m_IHight(300)
{
	memset(&m_WClassEx, 0, sizeof(m_WClassEx));

	GdiplusStartupInput gdipinput;
	GdiplusStartup(&token, &gdipinput, NULL);
}

CXqWindow::~CXqWindow()
{
	if (this->m_HWnd != NULL && ::IsWindow(this->m_HWnd)) // C++对象被销毁之前，销毁窗口对象
	{
		::DestroyWindow(this->m_HWnd);
	}
	GdiplusShutdown(token);
}

BOOL CXqWindow::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

HWND CXqWindow::GetHandle()
{
	return this->m_HWnd;
}

void CXqWindow::OnDraw(HDC hdc)
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

void CXqWindow::OnLButtonDown(HWND hwnd, int x, int y)
{

	InvalidateRect(hwnd, NULL, FALSE);
}

void CXqWindow::OnLButtonUp(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, FALSE);
}

void CXqWindow::OnMouseMove(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, FALSE);
}

void CXqWindow::OnSize(HWND hwnd, int w, int h)
{
	width = w;
	height = h;
	InvalidateRect(hwnd, NULL, FALSE);
}

void OnCreate(HWND hwnd)
{
}

void CXqWindow::Create()
{
	m_WClassEx.cbSize = sizeof(WNDCLASSEX);
	m_WClassEx.lpfnWndProc = WndProc;
	m_WClassEx.hInstance = m_HInstance;
	m_WClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	m_WClassEx.lpszClassName = L"windows";
	m_WClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_WClassEx)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return ;
	}

	m_HWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"windows", L"GDI+ [feijianshen]", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		m_IPosX,
		m_IPosY,
		m_IWidth,
		m_IHight,
		NULL, NULL, m_HInstance, NULL);

	if (m_HWnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return ;
	}
}

void CXqWindow::Create(LPCWSTR lpszClassName)
{
	memset(&m_WClassEx, 0, sizeof(m_WClassEx));
	m_WClassEx.cbSize = sizeof(WNDCLASSEX);
	m_WClassEx.lpfnWndProc = WndProc;
	m_WClassEx.hInstance = m_HInstance;
	m_WClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	m_WClassEx.lpszClassName = lpszClassName;
	m_WClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_WClassEx)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	m_HWnd = CreateWindowEx(WS_EX_CLIENTEDGE, lpszClassName, lpszClassName, WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		m_IPosX, 
		m_IPosY,
		m_IWidth,
		m_IHight,
		NULL, NULL, m_HInstance, NULL);

	if (m_HWnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
}


void CXqWindow::ShowWindow(int nCmdShow)
{
	::ShowWindow(m_HWnd, nCmdShow);
	UpdateWindow();
}

void CXqWindow::UpdateWindow(void)
{
	::UpdateWindow(m_HWnd);
}

WPARAM CXqWindow::MessageLoop(void)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



int CXqWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


LRESULT CALLBACK CXqWindow::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
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