#pragma once
#include <windows.h>
#include <tchar.h>

class CXqWindow
{
public:
	CXqWindow(HINSTANCE hInst);
	~CXqWindow();
public:
	virtual BOOL OnInitDialog(WPARAM wParam, LPARAM lParam);
	virtual int HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HWND GetHandle();
public:
	void Create();
	void Create(LPCWSTR lpszClassName);

	static void OnDraw(HDC hdc);
	void ShowWindow(int nCmdShow);
	void UpdateWindow(void);
	void SetWindowPos(int x, int y, int width, int hight, UINT uFlags);
	void MoveWindow(int x, int y, int width, int hight, BOOL bRepaint);

	static void OnLButtonDown(HWND hwnd, int x, int y);
	static void OnLButtonUp(HWND hwnd, int x, int y);
	static void OnMouseMove(HWND hwnd, int x, int y);
	static void OnSize(HWND hwnd, int w, int h);
	

	WPARAM MessageLoop(void);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND m_HWnd;
	WNDCLASSEX m_WClassEx;
	HINSTANCE m_HInstance;
	int m_IPosX;
	int m_IPosY;
	int m_IWidth;
	int m_IHight;
};

