#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK  wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
	switch (msgId)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
					   PostQuitMessage(0);
	}
		break;
	default:
		return DefWindowProc(hWnd, msgId, wParam, lParam);
	}
	return  0;

}

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//1 注册窗口类
	WNDCLASSEX  wnd;

	memset(&wnd, 0, sizeof(wnd));

	wnd.cbSize = sizeof(wnd);
	wnd.lpfnWndProc = wndProc;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = _T("windows");
	wnd.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClassEx(&wnd);
	//2 创建窗口
	HWND hWnd = CreateWindowEx(
		0
		, _T("windows")
		, _T("窗口标题")
		, WS_OVERLAPPEDWINDOW
		, 100
		, 100
		, 480
		, 320
		, 0
		, 0
		, hInstance
		, 0);

	//!3    更新显示
	if (hWnd)
	{
		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}

	MSG     msg = { 0 };
	//4 消息循环
	while (WM_QUIT != msg.message)
	{

		if (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	return  0;
}