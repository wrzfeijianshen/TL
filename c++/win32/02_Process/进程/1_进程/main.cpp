#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include "MyPress.h"


#define OPEN_CONSOLE_IN_DIALOG {\
	AllocConsole(); \
	freopen("CONOUT$", "w+t", stdout); \
	freopen("CONIN$", "r+t", stdin); }

#define CLOSE_CONSOLE_IN_DIALOG {\
	FreeConsole(); }
int g_ProcessCont = 1;

// BOOL WINAPI AllocConsole(void);

LRESULT CALLBACK    windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return  DefWindowProc(hWnd, msg, wParam, lParam);
}

int     WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
#ifdef _DEBUG
	AllocConsole();
	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	freopen_s(&fp,"CONIN$", "r+t", stdin);
#endif

#if 0 
	OPEN_CONSOLE_IN_DIALOG printf("aaa\n");
	std::cout << "aaa" << std::endl;
#endif

	//OPEN_CONSOLE_IN_DIALOG;
	//  1 注册窗口类
	::WNDCLASSEXA winClass;
	winClass.lpszClassName = "window";
	winClass.cbSize = sizeof(::WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	winClass.lpfnWndProc = windowProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = 0;
	winClass.hIconSm = 0;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)(GRAY_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	RegisterClassExA(&winClass);

	//  2 创建窗口
	HWND    hWnd = CreateWindowEx(
		NULL,
		TEXT("window"),
		TEXT("进程"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		200,
		200,
		500,
		500,
		0,
		0,
		hInstance,
		0
		);

	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);

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

		while (g_ProcessCont)
		{
			g_ProcessCont = 0;
			MyCreateProcess();
			Sleep(3000);
			MyClosePress();
		}
	}

	return  0;
}