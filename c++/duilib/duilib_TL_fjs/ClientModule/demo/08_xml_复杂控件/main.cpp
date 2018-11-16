#pragma once
#include "../../Duilib/UIlib.h"

using namespace DuiLib;

//////////////////////////////////////////////////////////////////////////
//Link

/*
*	Duilib
*/
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\..\\..\\PublicLibrary\\debug\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\..\\..\\PublicLibrary\\debug\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\..\\..\\PublicLibrary\\release\\DuiLib_u.lib")
#   else
#       pragma comment(lib, "..\\..\\..\\PublicLibrary\\release\\DuiLib.lib")
#   endif
#endif

class CDuiFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const   { return _T("DUIMainFrame"); }
	virtual CDuiString GetSkinFile()                { return _T("duilib.xml"); }
	virtual CDuiString GetSkinFolder()              { return _T(""); }

	virtual void       InitWindow()
	{
		CActiveXUI* pActiveXUI = static_cast<CActiveXUI*>(m_PaintManager.FindControl(_T("ActiveXDemo1")));

		if (pActiveXUI)
		{
			IWebBrowser2* pWebBrowser = NULL;

			pActiveXUI->SetDelayCreate(false);              // 相当于界面设计器里的DelayCreate属性改为FALSE，在duilib自带的FlashDemo里可以看到此属性为TRUE             
			pActiveXUI->CreateControl(CLSID_WebBrowser);    // 相当于界面设计器里的Clsid属性里填入{8856F961-340A-11D0-A96B-00C04FD705A2}，建议用CLSID_WebBrowser，如果想看相应的值，请见<ExDisp.h>
			pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);

			if (pWebBrowser != NULL)
			{
				//pWebBrowser->Navigate(L"https://code.google.com/p/duilib/",NULL,NULL,NULL,NULL);  
				pWebBrowser->Navigate(L"http://www.baidu.com/", NULL, NULL, NULL, NULL);  // 由于谷歌时不时被墙，所以换成反应快的网站
				pWebBrowser->Release();
			}
		}
		CProgressUI* pProgress = static_cast<CProgressUI*>(m_PaintManager.FindControl(_T("ProgressDemo1")));
		pProgress->SetValue(40);

		CSliderUI* pSlider = static_cast<CSliderUI*>(m_PaintManager.FindControl(_T("SliderDemo1")));
		pSlider->SetValue(40);
		CComboUI* pCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo1")));
		pCombo->SelectItem(1, false);

		CDuiString str;
		CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));

		// 添加List列表内容，必须先Add(pListElement)，再SetText
		for (int i = 0; i < 100; i++)
		{
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(i);
			pList->Add(pListElement);

			str.Format(_T("%d"), i);
			pListElement->SetText(0, str);
			str.Format(_T("No%d"), i);

			pListElement->SetText(1, str);
		}

	}

	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("selectchanged"))
		{
			CDuiString    strName = msg.pSender->GetName();
			CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));

			if (strName == _T("OptionDemo1"))
				pControl->SelectItem(0);
			else if (strName == _T("OptionDemo2"))
				pControl->SelectItem(1);
			else if (strName == _T("OptionDemo3"))
				pControl->SelectItem(2);
		}

		__super::Notify(msg);
	}

};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.CenterWindow();
	duiFrame.ShowModal();

	::CoUninitialize();
	return 0;
}