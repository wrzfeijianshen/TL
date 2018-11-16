#include "stdafx.h"
//#include "HelloDuilib.h"
class CHelloDuilibWnd :
	public WindowImplBase
{
public:
	CHelloDuilibWnd(void);
	~CHelloDuilibWnd(void);

protected:
	virtual CDuiString GetSkinFolder() { return _T("skin"); };
	virtual CDuiString GetSkinFile()  { return _T("HelloDuilib.xml"); };
	virtual LPCTSTR GetWindowClassName(void) const { return _T("HelloDuilib_Wnd"); };
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)

{
	CPaintManagerUI::SetInstance(hInstance);// 加载XML的时候，需要使用该句柄去定位EXE的路径，才能加载XML的路径

	CHelloDuilibWnd* wnd = new CHelloDuilibWnd; // 生成对象
//	wnd->Create(NULL, NULL, UI_WNDSTYLE_DIALOG, 0); // 创建DLG窗口
//	wnd->CenterWindow(); // 窗口居中
//	wnd->ShowWindow(); // 显示
//	CPaintManagerUI::MessageLoop(); // 消息循环

	//delete wnd; // 删除对象
}