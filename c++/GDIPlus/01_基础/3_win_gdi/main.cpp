#include "XqWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CXqWindow* pTest = new  CXqWindow(hInstance);
	pTest->Create(L"²âÊÔ");
	pTest->ShowWindow(nCmdShow);
	pTest->MoveWindow(0,0,1000,800,TRUE);

	WPARAM wMsg;
	wMsg = pTest->MessageLoop();

	return (int)wMsg;
}
