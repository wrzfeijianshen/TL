#include "XqWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CXqWindow* pTest = new  CXqWindow(hInstance);
	pTest->Create(L"²âÊÔ");
	pTest->ShowWindow(nCmdShow);
	WPARAM wMsg;
	wMsg = pTest->MessageLoop();

	return (int)wMsg;
}
