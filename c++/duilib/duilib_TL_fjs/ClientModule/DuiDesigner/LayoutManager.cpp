#include "StdAfx.h"
#include "LayoutManager.h"
#include "UIUtil.h"
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////
//CUserDefineUI
class CUserDefineUI : public CControlUI
{
public:
	virtual void SetClass(LPCTSTR className)
	{
		mClassName = className;
		mClassName += _T("UI");
	}
	virtual LPCTSTR GetClass() const
	{
		return mClassName;
	}

	virtual LPVOID GetInterface(LPCTSTR pstrName)
	{
		if (_tcscmp(pstrName, _T("UserDefinedControl")) == 0)
			return static_cast<CUserDefineUI*>(this);
		return NULL;
	}

	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		TRACE(_T("%s:%s\n"), pstrName, pstrValue);
		m_pAttributeList[CDuiString(pstrName)] = CDuiString(pstrValue);

		CControlUI::SetAttribute(pstrName, pstrValue);
	}

	virtual CDuiString GetName() const
	{
		CDuiString sValue = _T("");
		std::map<CDuiString, CDuiString>::const_iterator it = m_pAttributeList.find(_T("name"));
		if (it != m_pAttributeList.end())
			sValue = it->second;
		return sValue;
	}

	std::map<CDuiString, CDuiString> m_pAttributeList;
protected:
	CDuiString mClassName;
};


//////////////////////////////////////////////////////////////////////////
//CFormUI

CFormUI::CFormUI()
	: m_pFileRoot(nullptr)
{
}

CFormUI::~CFormUI()
{

}

LPCTSTR CFormUI::GetClass() const
{
	return _T("FormUI");
}

LPVOID CFormUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, _T("Form")) == 0)
		return static_cast<CFormUI*>(this);

	return CContainerUI::GetInterface(pstrName);
}

SIZE CFormUI::GetInitSize()
{
	return m_pManager->GetInitSize();
}

void CFormUI::SetInitSize(int cx, int cy)
{
	m_pManager->SetInitSize(cx, cy);

	SetPos(CRect(0, 0, cx, cy));
}

RECT& CFormUI::GetSizeBox()
{
	return m_pManager->GetSizeBox();
}

void CFormUI::SetSizeBox(RECT& rcSizeBox)
{
	m_pManager->SetSizeBox(rcSizeBox);
}

RECT& CFormUI::GetCaptionRect()
{
	return m_pManager->GetCaptionRect();
}

void CFormUI::SetCaptionRect(RECT& rcCaption)
{
	m_pManager->SetCaptionRect(rcCaption);
}

SIZE CFormUI::GetRoundCorner() const
{
	return m_pManager->GetRoundCorner();
}

void CFormUI::SetRoundCorner(int cx, int cy)
{
	m_pManager->SetRoundCorner(cx, cy);
}

SIZE CFormUI::GetMinInfo() const
{
	return m_pManager->GetMinInfo();
}

SIZE CFormUI::GetMaxInfo() const
{
	return m_pManager->GetMaxInfo();
}

void CFormUI::SetMinInfo(int cx, int cy)
{
	ASSERT(cx >= 0 && cy >= 0);
	m_pManager->SetMinInfo(cx, cy);
}

void CFormUI::SetMaxInfo(int cx, int cy)
{
	ASSERT(cx >= 0 && cy >= 0);
	m_pManager->SetMaxInfo(cx, cy);
}

bool CFormUI::IsShowUpdateRect() const
{
	return m_pManager->IsShowUpdateRect();
}

void CFormUI::SetShowUpdateRect(bool bShow)
{
	m_pManager->SetShowUpdateRect(bShow);
}

void CFormUI::SetPos(RECT rc)
{
	CControlUI::SetPos(rc);
	m_cxyFixed.cx = rc.right - rc.left;
	m_cxyFixed.cy = rc.bottom - rc.top;

	if (m_items.GetSize() == 0) return;
	CControlUI* pControl = static_cast<CControlUI*>(m_items[0]);
	if (pControl == NULL) return;

	//放大到整个客户区
	pControl->SetPos(rc);
}

void CFormUI::SetFileRoot(CControlUI* pFileRoot)
{
	m_pFileRoot = pFileRoot;
}

CControlUI* CFormUI::GetFileRoot()
{
	return m_pFileRoot;
}

void CFormUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("size")) == 0)
	{
		LPTSTR pstr = NULL;
		int cx = _tcstol(pstrValue, &pstr, 10);				ASSERT(pstr);
		int cy = _tcstol(pstr + 1, &pstr, 10);				ASSERT(pstr);
		SetInitSize(cx, cy);
		return;
	}
	else if (_tcscmp(pstrName, _T("sizebox")) == 0)
	{
		RECT rcSizeBox = { 0 };
		LPTSTR pstr = NULL;
		rcSizeBox.left = _tcstol(pstrValue, &pstr, 10);		ASSERT(pstr);
		rcSizeBox.top = _tcstol(pstr + 1, &pstr, 10);		ASSERT(pstr);
		rcSizeBox.right = _tcstol(pstr + 1, &pstr, 10);		ASSERT(pstr);
		rcSizeBox.bottom = _tcstol(pstr + 1, &pstr, 10);	ASSERT(pstr);
		SetSizeBox(rcSizeBox);
		return;
	}
	else if (_tcscmp(pstrName, _T("caption")) == 0)
	{
		RECT rcCaption = { 0 };
		LPTSTR pstr = NULL;
		rcCaption.left = _tcstol(pstrValue, &pstr, 10);		ASSERT(pstr);
		rcCaption.top = _tcstol(pstr + 1, &pstr, 10);		ASSERT(pstr);
		rcCaption.right = _tcstol(pstr + 1, &pstr, 10);		ASSERT(pstr);
		rcCaption.bottom = _tcstol(pstr + 1, &pstr, 10);	ASSERT(pstr);
		SetCaptionRect(rcCaption);
		return;
	}
	else if (_tcscmp(pstrName, _T("roundcorner")) == 0)
	{
		LPTSTR pstr = NULL;
		int cx = _tcstol(pstrValue, &pstr, 10);				ASSERT(pstr);
		int cy = _tcstol(pstr + 1, &pstr, 10);				ASSERT(pstr);
		SetRoundCorner(cx, cy);
		return;
	}
	else if (_tcscmp(pstrName, _T("mininfo")) == 0)
	{
		LPTSTR pstr = NULL;
		int cx = _tcstol(pstrValue, &pstr, 10);				ASSERT(pstr);
		int cy = _tcstol(pstr + 1, &pstr, 10);				ASSERT(pstr);
		SetMinInfo(cx, cy);
		return;
	}
	else if (_tcscmp(pstrName, _T("maxinfo")) == 0)
	{
		LPTSTR pstr = NULL;
		int cx = _tcstol(pstrValue, &pstr, 10);				ASSERT(pstr);
		int cy = _tcstol(pstr + 1, &pstr, 10);				ASSERT(pstr);
		SetMaxInfo(cx, cy);
		return;
	}
	else if (_tcscmp(pstrName, _T("showdirty")) == 0)
	{
		SetShowUpdateRect(_tcscmp(pstrValue, _T("true")) == 0);
		return;
	}
	else if (_tcscmp(pstrName, _T("pos")) == 0)
	{
		RECT rcPos = { 0 };
		LPTSTR pstr = NULL;
		rcPos.left = _tcstol(pstrValue, &pstr, 10);			ASSERT(pstr);
		rcPos.top = _tcstol(pstr + 1, &pstr, 10);			ASSERT(pstr);
		rcPos.right = _tcstol(pstr + 1, &pstr, 10);			ASSERT(pstr);
		rcPos.bottom = _tcstol(pstr + 1, &pstr, 10);		ASSERT(pstr);
		SetInitSize(rcPos.right - rcPos.left, rcPos.bottom - rcPos.top);
		return;
	}
	else if (_tcscmp(pstrName, _T("alpha")) == 0)
	{
		SetAlpha(_ttoi(pstrValue));
		return;
	}
	else if (_tcscmp(pstrName, _T("bktrans")) == 0)
	{
		SetBackgroundTransparent(_tcscmp(pstrValue, _T("true")) == 0);
		return;
	}
	else if (_tcscmp(pstrName, _T("defaultfontcolor")) == 0)
	{
		while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetDefaultFontColor(clrColor);
		return;
	}
	else if (_tcscmp(pstrName, _T("selectedcolor")) == 0)
	{
		while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetDefaultSelectedFontColor(clrColor);
		return;
	}
	else if (_tcscmp(pstrName, _T("disabledfontcolor")) == 0)
	{
		while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetDefaultDisabledFontColor(clrColor);
		return;
	}
	else if (_tcscmp(pstrName, _T("linkfontcolor")) == 0)
	{
		while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetDefaultLinkFontColor(clrColor);
		return;
	}
	else if (_tcscmp(pstrName, _T("linkhoverfontcolor")) == 0)
	{
		while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetDefaultLinkHoverFontColor(clrColor);
		return;
	}
}

void CFormUI::SetBackgroundTransparent(bool bTrans)
{
	m_pManager->SetBackgroundTransparent(bTrans);
}

bool CFormUI::GetBackgroundTransparent() const
{
	return m_pManager->GetBackgroundTransparent();
}

void CFormUI::SetDefaultDisabledFontColor(DWORD dwColor)
{
	m_pManager->SetDefaultDisabledColor(dwColor);
}

DWORD CFormUI::GetDefaultDisabledFontColor() const
{
	return m_pManager->GetDefaultDisabledColor();
}

void CFormUI::SetDefaultFontColor(DWORD dwColor)
{
	m_pManager->SetDefaultFontColor(dwColor);
}

DWORD CFormUI::GetDefaultFontColor() const
{
	return m_pManager->GetDefaultFontColor();
}

void CFormUI::SetDefaultLinkFontColor(DWORD dwColor)
{
	m_pManager->SetDefaultLinkFontColor(dwColor);
}

DWORD CFormUI::GetDefaultLinkFontColor() const
{
	return m_pManager->GetDefaultLinkFontColor();
}

void CFormUI::SetDefaultLinkHoverFontColor(DWORD dwColor)
{
	m_pManager->SetDefaultLinkHoverFontColor(dwColor);
}

DWORD CFormUI::GetDefaultLinkHoverFontColor() const
{
	return m_pManager->GetDefaultLinkHoverFontColor();
}

void CFormUI::SetDefaultSelectedFontColor(DWORD dwColor)
{
	m_pManager->SetDefaultSelectedBkColor(dwColor);
}

DWORD CFormUI::GetDefaultSelectedFontColor() const
{
	return m_pManager->GetDefaultSelectedBkColor();
}

void CFormUI::SetAlpha(int iOpacity)
{
	m_pManager->SetTransparent(iOpacity);
}

int CFormUI::GetAlpha() const
{
	return m_pManager->GetTransparent();
}

//////////////////////////////////////////////////////////////////////////
//CFormTestWnd

CFormTestWnd* CFormTestWnd::g_instance = NULL;

CFormTestWnd* CFormTestWnd::getInstance(CDuiString strXmlFile)
{
	if (g_instance == NULL)
		g_instance = new CFormTestWnd(strXmlFile);

	return g_instance;
}

CFormTestWnd::CFormTestWnd(CDuiString strXmlFile)
	: m_strXmlFile(strXmlFile)
{

}

CFormTestWnd::~CFormTestWnd()
{

}

CDuiString CFormTestWnd::GetSkinFolder()
{
	return _T("");
}

CDuiString CFormTestWnd::GetSkinFile()
{
	return m_strXmlFile;
}

LPCTSTR CFormTestWnd::GetWindowClassName() const
{
	return _T("UIFormTest");
}

UILIB_RESOURCETYPE CFormTestWnd::GetResourceType() const
{
	return DuiLib::UILIB_FILE;
}

UINT CFormTestWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_CHILD;
}

void CFormTestWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	SAFE_DELETE(g_instance);
}

LRESULT CFormTestWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		Close();
		PostMessage(WM_QUIT, wParam, 0L);
	}
	return FALSE;
}

void CFormTestWnd::InitWindow()
{
	// init window when create window
}

CControlUI* CFormTestWnd::CreateControl(LPCTSTR pstrClassName)
{
	//暂时不支持嵌套(因为不确定文件路径)
	//if (_tcsicmp(pstrClassName, _T("")) != 0)
	//{
	//	CDuiString strCompletePath = m_PaintManager.GetResourcePath() + pstrClassName + _T(".xml");
	//	if (::PathFileExists(strCompletePath.GetData()))
	//	{
	//		int nPos = -1;
	//		CDuiString strFilePath;
	//		nPos = m_strXmlFile.ReverseFind(_T('\\'));
	//		if (nPos != -1)
	//			strFilePath = m_strXmlFile.Left(nPos + 1);
	//		strFilePath += pstrClassName;
	//		strFilePath += _T(".xml");

	//		CDialogBuilder builder;
	//		CControlUI* userPanel = static_cast<CControlUI*>(builder.Create(strFilePath.GetData(), (UINT)0, this, &m_PaintManager));

	//		return userPanel;
	//	}
	//}
	return NULL;
}

void CFormTestWnd::CreateFrame()
{
	if (0 == IsWindow(m_hWnd))
	{
		HWND hWnd = ::AfxGetMainWnd()->m_hWnd;
		int style = UI_CLASSSTYLE_DIALOG | WS_MINIMIZEBOX;
		m_hWnd = this->Create(hWnd, _T("RegistFrame"), style, 0L);
		this->CenterWindow();

		if (true)
			//模式对话框
			this->ShowModal();
		else
			//非模式对话框
			::ShowWindow(*this, SW_NORMAL);
	}
	else
		::SwitchToThisWindow(m_hWnd, true);
}

void CFormTestWnd::InitData(TNotifyUI& msg)
{
	// init data after create window
}

void CFormTestWnd::Notify(TNotifyUI& msg)
{
	CDuiString type = msg.sType;
	CDuiString name = msg.pSender->GetName();

	if (_tcscmp(type, DUI_MSGTYPE_WINDOWINIT) == 0)
	{
		this->InitData(msg);
	}
	else if (_tcscmp(msg.sType, DUI_MSGTYPE_CLICK) == 0)
	{
	}
}

//////////////////////////////////////////////////////////////////////////
//CLayoutManager

CLayoutManager::CLayoutManager(void)
	: m_pFormUI(NULL)
	, m_bShowGrid(false)
	, m_bShowAuxBorder(true)
{
}

CLayoutManager::~CLayoutManager(void)
{
}

CControlUI* CLayoutManager::CreateControl(LPCTSTR pstrClass)
{
	CUserDefineUI* pResult = new CUserDefineUI;
	if (pResult)
	{
		pResult->SetClass(pstrClass);
	}
	return pResult;
}

int CALLBACK CLayoutManager::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData) {
	TCHAR szDir[MAX_PATH];
	ZeroMemory(szDir, sizeof(szDir));

	switch (uMsg) {
		case BFFM_INITIALIZED: {			//初始化消息

			_stprintf_s(szDir, _T("%s"), CLayoutManager::m_strSkinDir);
			::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)szDir);

			//关于BFFM_SETSELECTION消息的说明

			//wParam ：标记lParam参数包含一个ITEMIDLIST结构(PIDL)还是一个目录路径名

			//          如果为TRUE，lParam内容为路径名；否则lParam包含一个路径PIDL。

			//lParam ：内容为浏览对话框所选的路径。如果wParam为TRUE，lParam内容为一个

			//         以NULL结尾的字符串的指针，否则为PIDL

		}break;

		case BFFM_SELCHANGED: {				//选择路径变化
			// Set the status window to the currently selected path.
			if (SHGetPathFromIDList((LPITEMIDLIST)lp, szDir)) {
				::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szDir);
			}
		}break;

		case BFFM_VALIDATEFAILED: {			//路径无效

			//仅当目录浏览对话框中含有编辑框并且设置了BIF_VALIDATE标记才可能出现此消息
			//即BROWSEINFO结构中ulFlags含有BIF_EDITBOX|BIF_VALIDATE标志
			//返回0允许对话框提前关闭，SHBrowseForFolder()返回NULL
			//返回1对话框继续显示，因为对话框仍继续显示，可以在状态行显示出错消息

			CDuiString strTip = _T("无效的目录，请重新选择");
			AfxMessageBox(strTip);
			return 1;
		}break;

		default:
			break;
	}
	return 0;
}

CDuiString CLayoutManager::ShowBrowseDlg(HWND hWnd, LPCTSTR lpStr)
{
	TCHAR szPath[MAX_PATH];						//存放选择的目录路径
	ZeroMemory(szPath, sizeof(szPath));
	_stprintf_s(szPath, _T("%s"), lpStr);

	BROWSEINFO bi;
	bi.hwndOwner = hWnd;
	bi.pidlRoot = NULL;							//初始化制定的root目录很不容易
	bi.pszDisplayName = szPath;					//此参数如为NULL则不能显示对话框  
	bi.lpszTitle = _T("请选择资源的目录:");
	bi.ulFlags = BIF_EDITBOX | BIF_VALIDATE;	//浏览对话框中包含一个编辑框
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = 0;								//设置默认路径
	bi.iImage = IDR_MAINFRAME;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	CString str;
	if (lp)
	{
		//调用显示选择对话框
		SHGetPathFromIDList(lp, szPath);
		str.Format(_T("资源路径为: %s"), szPath);
		AfxMessageBox(str);
		return szPath;
	}
	else
	{
		delete m_pFormUI;
		m_pFormUI = nullptr;
		exit(0);

		//退出程序
		//AfxGetMainWnd()->SendMessage(WM_CLOSE);

		//关闭当前窗口
		//AfxGetMainWnd()->DestroyWindow();

		//关闭模式对话框
		//EndDialog(0);
	}

	return _T("");
}

void CLayoutManager::Init(HWND hWnd, LPCTSTR pstrLoad)
{
	//计算路径
	int nPos = -1;
	if (*pstrLoad != '\0')
	{
		m_strSkinDir = pstrLoad;
		nPos = m_strSkinDir.ReverseFind(_T('\\'));
		if (nPos != -1)
			m_strSkinDir = m_strSkinDir.Left(nPos + 1);

		g_HookAPI.SetSkinDir(m_strSkinDir);
		g_HookAPI.EnableCreateFile(true);
	}

	//设置资源路径
	CDuiString resourcePath = ShowBrowseDlg(hWnd, pstrLoad);
	HINSTANCE hInstance = ::AfxGetInstanceHandle();
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(resourcePath);

	if (_tcscmp(pstrLoad, _T("")) != 0)
	{
		//检测资源路径
		CDuiString sTempPath;
		if (FALSE == CLayoutManager::ConvertSurplusFileName(sTempPath, pstrLoad))
		{
			//如果匹配资源路径失败,则取默认值
			CPaintManagerUI::SetResourcePath(m_strSkinDir);
			sTempPath = pstrLoad;
			pstrLoad = sTempPath.Right(sTempPath.GetLength() - nPos - 1);
		}
	}

	//init CPaintManagerUI
	m_Manager.Init(hWnd);

	//init CFormUI Root Control
	::CRect rcWinRect = { 0, 0, 0, 0 };
	CControlUI* pControl = CLayoutManager::NewUI(classWindow, rcWinRect, NULL, NULL);
	m_pFormUI = static_cast<CFormUI*>(pControl);
	m_pFormUI->GetInterface(_T("Form"));
	ASSERT(m_pFormUI);
	m_pFormUI->SetManager(&m_Manager, NULL);

	//load xml ui
	this->__LoadXmlUI(pstrLoad);
}

void CLayoutManager::__LoadXmlUI(LPCTSTR pstrLoad, bool bAttachDialog /* = true */)
{
	//init xml
	SIZE size = { 0, 0 };
	CDialogBuilder builder;
	CPaintManagerUI* pManager = m_pFormUI->GetManager();
	CControlUI* pRoot = builder.Create(pstrLoad, (UINT)0, this, pManager);
	if (pRoot)
	{
		m_pFormUI->SetFileRoot(pRoot);
		m_pFormUI->Add(pRoot);
		size = pManager->GetInitSize();

		int goIndex = 0;
	lab_setsize:
		++goIndex;
		if (size.cx <= 0 || size.cy <= 0)
		{
			switch (goIndex)
			{
				case 1:
				{
					RECT rc = pRoot->GetPos();
					size.cx = rc.right - rc.left;
					size.cy = rc.bottom - rc.top;
				}break;

				case 2:
				{
					size.cx = pRoot->GetFixedWidth();
					size.cy = pRoot->GetFixedHeight();
				}break;

				default:
				{
					size.cx = 1024;//FORM_INIT_WIDTH;
					size.cy = 738;// FORM_INIT_HEIGHT;
				}break;
			}

			if (size.cx <= 0 || size.cy <= 0)
				goto lab_setsize;
		}
	}
	else
	{
		size.cx = FORM_INIT_WIDTH;
		size.cy = FORM_INIT_HEIGHT;
	}
	m_pFormUI->SetInitSize(size.cx, size.cy);
	m_pFormUI->SetAlpha(pManager->GetTransparent());
	m_pFormUI->SetBackgroundTransparent(pManager->GetBackgroundTransparent());

	if (bAttachDialog)
		pManager->AttachDialog(m_pFormUI);
}

void CLayoutManager::Reload(LPCTSTR pstrLoad)
{
	//清除所有缓存图片内存
	CPaintManagerUI* pManager = m_pFormUI->GetManager();
	if (pManager)
	{
		pManager->RemoveAllImages();				//移除所有缓存图片
		pManager->RemoveAllFonts();					//移除所有字体
		pManager->RemoveAllDefaultAttributeList();	//移除所有默认属性列表
		pManager->RemoveAllOptionGroups();			//移除所有"group"数组
		pManager->RemoveAllTimers();				//移除所有定时器
	}

	if (_tcscmp(pstrLoad, _T("")) != 0)
	{
		//检测资源路径
		CDuiString sTempPath;
		CLayoutManager::ConvertSurplusFileName(sTempPath, pstrLoad, true);
	}

	__LoadXmlUI(pstrLoad, false);
}

void CLayoutManager::Draw(CDC* pDC)
{
	CSize szInitSize = m_pFormUI->GetInitSize();
	CRect rcPaint(0, 0, szInitSize.cx, szInitSize.cy);

	m_pFormUI->DoPaint(pDC->GetSafeHdc(), rcPaint);
	DrawAuxBorder(pDC, m_pFormUI->GetItemAt(0));
	DrawGrid(pDC, rcPaint);
}

void CLayoutManager::DrawAuxBorder(CDC* pDC, CControlUI* pControl)
{
	if (!m_bShowAuxBorder || pControl == NULL || !pControl->IsVisible())
		return;

	CContainerUI* pContainer = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));

	//draw auxBorder
	if (pControl->GetBorderColor() == 0 || pControl->GetBorderSize() <= 0)
	{
		pDC->SetBkMode(TRANSPARENT);
		CPen DotedPen(PS_SOLID, 1, pContainer ? RGB(255, 0, 0) : RGB(0, 255, 0));
		CPen* pOldPen;
		CBrush* pOldBrush;
		pOldPen = pDC->SelectObject(&DotedPen);
		pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		CRect rect = pControl->GetPos();
		pDC->Rectangle(&rect);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}

	if (pContainer == NULL)
		return;
	for (int i = 0; i < pContainer->GetCount(); i++)
	{
		DrawAuxBorder(pDC, pContainer->GetItemAt(i));
	}
}

void CLayoutManager::DrawGrid(CDC* pDC, CRect& rect)
{
	if (!m_bShowGrid)
		return;

	for (int i = rect.left; i < rect.right; i += 10)
	{
		for (int j = rect.top; j < rect.bottom; j += 10)
			pDC->SetPixel(i, j, RGB(0, 0, 0));
	}
}

CControlUI* CLayoutManager::NewUI(int nClass, CRect& rect, CControlUI* pParent, CLayoutManager* pLayout)
{
	CControlUI* pControl = NULL;
	ExtendedAttributes* pExtended = new ExtendedAttributes;
	ZeroMemory(pExtended, sizeof(ExtendedAttributes));
	switch (nClass)
	{
		case classWindow:
			pControl = new CFormUI;
			pExtended->nClass = classWindow;
			pExtended->nDepth = 0;
			pControl->SetName(pControl->GetClass());
			break;
		case classControl:
			pControl = new CControlUI;
			pExtended->nClass = classControl;
			pControl->SetFloat(true);
			break;
		case classLabel:
			pControl = new CLabelUI;
			pExtended->nClass = classLabel;
			pControl->SetFloat(true);
			break;
		case classText:
			pControl = new CTextUI;
			pExtended->nClass = classText;
			pControl->SetFloat(true);
			break;
		case classButton:
			pControl = new CButtonUI;
			pExtended->nClass = classButton;
			pControl->SetFloat(true);
			break;
		case classEdit:
			pControl = new CEditUI;
			pExtended->nClass = classEdit;
			pControl->SetFloat(true);
			break;
		case classRichEdit:
			pControl = new CRichEditUI;
			pExtended->nClass = classRichEdit;
			pControl->SetFloat(true);
			pControl->SetBkColor(0xFFFFFFFF);
			break;
		case classOption:
			pControl = new COptionUI;
			pExtended->nClass = classOption;
			pControl->SetFloat(true);
			break;
		case classProgress:
			pControl = new CProgressUI;
			pExtended->nClass = classProgress;
			pControl->SetFloat(true);
			break;
		case classSlider:
			pControl = new CSliderUI;
			pExtended->nClass = classSlider;
			pControl->SetFloat(true);
			break;
		case classCombo:
			pControl = new CComboUI;
			pExtended->nClass = classCombo;
			pControl->SetFloat(true);
			break;
		case classList:
			pControl = new CListUI;
			pExtended->nClass = classList;
			pControl->SetFloat(false);
			break;
		case classActiveX:
			pControl = new CActiveXUI;
			pExtended->nClass = classActiveX;
			break;
		case classContainer:
			pControl = new CContainerUI;
			pExtended->nClass = classContainer;
			break;
		case classVerticalLayout:
			pControl = new CVerticalLayoutUI;
			pExtended->nClass = classVerticalLayout;
			break;
		case classHorizontalLayout:
			pControl = new CHorizontalLayoutUI;
			pExtended->nClass = classHorizontalLayout;
			break;
		case classTileLayout:
			pControl = new CTileLayoutUI;
			pExtended->nClass = classTileLayout;
			break;
		case classTabLayout:
			pControl = new CTabLayoutUI;
			pExtended->nClass = classTabLayout;
			break;
		case classScrollBar:
			pControl = new CScrollBarUI;
			pExtended->nClass = classScrollBar;
			break;
		default:
			delete pExtended;
			return NULL;
	}
	if (pControl == NULL)
	{
		delete pExtended;
		return NULL;
	}
	pControl->SetTag((UINT_PTR)pExtended);

	//pos
	CRect rcParent = pParent ? pParent->GetPos() : CRect(0, 0, 0, 0);
	pControl->SetFixedXY(CSize(rect.left - rcParent.left, rect.top - rcParent.top));
	pControl->SetFixedWidth(rect.right - rect.left);
	pControl->SetFixedHeight(rect.bottom - rect.top);

	//close the delayed destory function
	CContainerUI* pContainer = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));
	if (pContainer)
		pContainer->SetDelayedDestroy(false);

	if (pParent)
	{
		CContainerUI* pParentContainer = static_cast<CContainerUI*>(pParent->GetInterface(_T("Container")));
		ASSERT(pParentContainer);
		if (!pParentContainer->Add(pControl))
		{
			delete pExtended;
			delete pControl;
			return NULL;
		}
		ExtendedAttributes* pParentExtended = (ExtendedAttributes*)pParentContainer->GetTag();
		pExtended->nDepth = pParentExtended->nDepth + 1;
		pParent->SetPos(pParent->GetPos());

		if (!pControl->IsFloat())
		{
			pControl->SetFixedWidth(pParent->GetFixedWidth());
			pControl->SetFixedHeight(pParent->GetFixedHeight());
		}
	}

	if (pLayout)
	{
		CPaintManagerUI* pManager = pLayout->GetManager();
		pControl->SetManager(pManager, pParent);

		//default attributes
		CString strClass = pControl->GetClass();
		strClass = strClass.Left(strClass.GetLength() - 2);
		LPCTSTR pDefaultAttributes = pManager->GetDefaultAttributeList(strClass);
		if (pDefaultAttributes)
			pControl->ApplyAttributeList(pDefaultAttributes);

		//name
		pLayout->SetDefaultUIName(pControl);
	}

	return pControl;
}

BOOL CLayoutManager::DeleteUI(CControlUI* pControl)
{
	if (pControl == NULL)
		return FALSE;

	ReleaseExtendedAttrib(pControl, pControl->GetManager());
	CControlUI* pParent = pControl->GetParent();
	if (pParent)
	{
		CContainerUI* pContainer = static_cast<CContainerUI*>(pParent->GetInterface(_T("Container")));
		pContainer->Remove(pControl);
	}
	else
		delete pControl;

	return TRUE;
}

void CLayoutManager::ReleaseExtendedAttrib(CControlUI* pControl, CPaintManagerUI* pManager)
{
	if (pControl == NULL)
		return;

	ExtendedAttributes* pExtended = (ExtendedAttributes*)pControl->GetTag();
	delete pExtended;
	pControl->SetTag(NULL);
	if (pManager)
		pManager->ReapObjects(pControl);

	CContainerUI* pContainer = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));
	if (pContainer != NULL)
	{
		int nCount = pContainer->GetCount();
		for (int i = 0; i < nCount; i++)
			ReleaseExtendedAttrib(pContainer->GetItemAt(i), pManager);
	}
}

CPaintManagerUI* CLayoutManager::GetManager()
{
	return &m_Manager;
}

CFormUI* CLayoutManager::GetForm() const
{
	return m_pFormUI;
}

CControlUI* CLayoutManager::FindControl(CPoint point) const
{
	return m_Manager.FindControl(point);
}

CLayoutManager::CDelayRepos::CDelayRepos()
{
}

CLayoutManager::CDelayRepos::~CDelayRepos()
{
	m_arrDelay.RemoveAll();
}

BOOL CLayoutManager::CDelayRepos::AddParent(CControlUI* pControl)
{
	if (pControl == NULL)
		return FALSE;

	for (int i = 0; i < m_arrDelay.GetSize(); i++)
	{
		CControlUI* pParent = m_arrDelay.GetAt(i);

		if (pControl == pParent)
			return FALSE;
	}
	m_arrDelay.Add(pControl);

	return TRUE;
}

void CLayoutManager::CDelayRepos::Repos()
{
	for (int i = 0; i < m_arrDelay.GetSize(); i++)
	{
		CControlUI* pParent = m_arrDelay.GetAt(i);

		pParent->SetPos(pParent->GetPos());
	}
}

void CLayoutManager::TestForm(LPCTSTR pstrFile)
{
	CDuiString sTempPath;
	CLayoutManager::ConvertSurplusFileName(sTempPath, pstrFile);

	CFormTestWnd* pFrame = CFormTestWnd::getInstance(pstrFile);
	if (!pFrame) return;

	pFrame->CreateFrame();
	g_HookAPI.EnableInvalidate(false);

	//开始消息循环
	CPaintManagerUI::MessageLoop();

	g_HookAPI.EnableInvalidate(true);

	CDuiString sFilePath = CPaintManagerUI::GetResourcePath();
	sFilePath += pstrFile;
	::DeleteFile(sFilePath);
}

BOOL CLayoutManager::IsEmptyForm() const
{
	return GetForm()->GetItemAt(0) == NULL;
}

CControlUI* CLayoutManager::CloneControls(CControlUI* pControl)
{
	if (pControl == NULL)
		return NULL;

	CContainerUI* pContainer = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));
	if (pContainer == NULL)
		return CloneControl(pControl);

	CContainerUI* pCopyContainer = static_cast<CContainerUI*>(CloneControl(pContainer)->GetInterface(_T("Container")));
	pCopyContainer->SetAutoDestroy(false);
	pCopyContainer->RemoveAll();
	pCopyContainer->SetAutoDestroy(true);
	for (int i = 0; i < pContainer->GetCount(); i++)
	{
		CControlUI* pCopyControl = CloneControls(pContainer->GetItemAt(i));
		pCopyControl->SetManager(NULL, pCopyContainer);
		pCopyContainer->Add(pCopyControl);
	}

	return pCopyContainer;
}

CControlUI* CLayoutManager::CloneControl(CControlUI* pControl)
{
	CControlUI* pCopyControl = NULL;
	int nClass = ((ExtendedAttributes*)pControl->GetTag())->nClass;
	switch (nClass)
	{
		case classControl:
			pCopyControl = new CControlUI(*static_cast<CControlUI*>(pControl->GetInterface(_T("Control"))));
			break;
		case classLabel:
			pCopyControl = new CLabelUI(*static_cast<CLabelUI*>(pControl->GetInterface(_T("Label"))));
			break;
		case classText:
			pCopyControl = new CTextUI(*static_cast<CTextUI*>(pControl->GetInterface(_T("Text"))));
			break;
		case classButton:
			pCopyControl = new CButtonUI(*static_cast<CButtonUI*>(pControl->GetInterface(_T("Button"))));
			break;
		case classEdit:
			pCopyControl = new CEditUI(*static_cast<CEditUI*>(pControl->GetInterface(_T("Edit"))));
			break;
		case classRichEdit:
			pCopyControl = new CRichEditUI(*static_cast<CRichEditUI*>(pControl->GetInterface(_T("RichEdit"))));
			break;
		case classOption:
			pCopyControl = new COptionUI(*static_cast<COptionUI*>(pControl->GetInterface(_T("Option"))));
			break;
		case classProgress:
			pCopyControl = new CProgressUI(*static_cast<CProgressUI*>(pControl->GetInterface(_T("Progress"))));
			break;
		case classSlider:
			pCopyControl = new CSliderUI(*static_cast<CSliderUI*>(pControl->GetInterface(_T("Slider"))));
			break;
		case classCombo:
			pCopyControl = new CComboUI(*static_cast<CComboUI*>(pControl->GetInterface(_T("Combo"))));
			break;
		case classActiveX:
			pCopyControl = new CActiveXUI(*static_cast<CActiveXUI*>(pControl->GetInterface(_T("ActiveX"))));
			break;
		case classContainer:
			pCopyControl = new CContainerUI(*static_cast<CContainerUI*>(pControl->GetInterface(_T("Container"))));
			break;
		case classChildLayout:
			pCopyControl = new CChildLayoutUI(*static_cast<CChildLayoutUI*>(pControl->GetInterface(_T("ChildLayout"))));
			break;
		case classVerticalLayout:
			pCopyControl = new CVerticalLayoutUI(*static_cast<CVerticalLayoutUI*>(pControl->GetInterface(_T("VerticalLayout"))));
			break;
		case classHorizontalLayout:
			pCopyControl = new CHorizontalLayoutUI(*static_cast<CHorizontalLayoutUI*>(pControl->GetInterface(_T("HorizontalLayout"))));
			break;
		case classTileLayout:
			pCopyControl = new CTileLayoutUI(*static_cast<CTileLayoutUI*>(pControl->GetInterface(_T("TileLayout"))));
			break;
		case classTabLayout:
			pCopyControl = new CTabLayoutUI(*static_cast<CTabLayoutUI*>(pControl->GetInterface(_T("TabLayout"))));
			break;
		case classListHeaderItem:
			pCopyControl = new CListHeaderItemUI(*static_cast<CListHeaderItemUI*>(pControl->GetInterface(_T("ListHeaderItem"))));
			break;
		case classListTextElement:
			pCopyControl = new CListTextElementUI(*static_cast<CListTextElementUI*>(pControl->GetInterface(_T("ListTextElement"))));
			break;
		case classListLabelElement:
			pCopyControl = new CListLabelElementUI(*static_cast<CListLabelElementUI*>(pControl->GetInterface(_T("ListLabelElement"))));
			break;
		case classListContainerElement:
			pCopyControl = new CListContainerElementUI(*static_cast<CListContainerElementUI*>(pControl->GetInterface(_T("ListContainerElement"))));
			break;
		case classWebBrowser:
			pCopyControl = new CWebBrowserUI(*static_cast<CWebBrowserUI*>(pControl->GetInterface(_T("WebBrowser"))));
			break;
		case classList:
		{//0917 by 邓景仁(cddjr) , 在不改动duilib的前提下，只能采用如下代码 
			CListUI &copyList = *static_cast<CListUI*>(pControl->GetInterface(_T("List")));
			if (copyList.GetHorizontalScrollBar() || copyList.GetVerticalScrollBar())
			{//测试窗体中，暂不支持滚动条
				copyList.EnableScrollBar(false, false);
			}
			pCopyControl = new CListUI();
			*(((CListUI*)pCopyControl)->GetHeader()) = *(copyList.GetHeader());
			*((CVerticalLayoutUI*)((CListUI*)pCopyControl)->GetList()) = *static_cast<CVerticalLayoutUI*>(copyList.GetList());
		}
		break;
		case classScrollBar:
			pCopyControl = new CScrollBarUI(*static_cast<CScrollBarUI*>(pControl->GetInterface(_T("ScrollBar"))));
			break;
		default:
			pCopyControl = new CUserDefineUI(*static_cast<CUserDefineUI*>(pControl));
			break;
	}

	return pCopyControl;
}

void CLayoutManager::AlignLeft(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	SIZE szXYLeft = pFocused->GetFixedXY();

	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pFocused->GetParent())
			continue;

		SIZE szXY = pControl->GetFixedXY();
		szXY.cx = szXYLeft.cx;
		pControl->SetFixedXY(szXY);
	}

	CControlUI* pParent = pFocused->GetParent();
	if (pParent)
		pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignRight(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	SIZE szXYRight = pFocused->GetFixedXY();
	int nWidth = pFocused->GetFixedWidth();

	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pFocused->GetParent())
			continue;

		SIZE szXY = pControl->GetFixedXY();
		szXY.cx = szXYRight.cx + nWidth - pControl->GetFixedWidth();
		pControl->SetFixedXY(szXY);
	}

	CControlUI* pParent = pFocused->GetParent();
	if (pParent)
		pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignTop(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	SIZE szXYTop = pFocused->GetFixedXY();

	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pFocused->GetParent())
			continue;

		SIZE szXY = pControl->GetFixedXY();
		szXY.cy = szXYTop.cy;
		pControl->SetFixedXY(szXY);
	}

	CControlUI* pParent = pFocused->GetParent();
	if (pParent)
		pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignBottom(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	SIZE szXYBottom = pFocused->GetFixedXY();
	int nHeight = pFocused->GetFixedHeight();

	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pFocused->GetParent())
			continue;

		SIZE szXY = pControl->GetFixedXY();
		szXY.cy = szXYBottom.cy + nHeight - pControl->GetFixedHeight();
		pControl->SetFixedXY(szXY);
	}

	CControlUI* pParent = pFocused->GetParent();
	if (pParent)
		pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignCenterVertically(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	CControlUI* pParent = pFocused->GetParent();
	if (!pParent)
		return;

	RECT rcParent = pParent->GetPos();

	CRect rectUnion;
	rectUnion.SetRectEmpty();
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pParent)
		{
			arrSelected.RemoveAt(i);
			continue;
		}

		rectUnion.UnionRect(&rectUnion, &pControl->GetPos());
	}

	int nOffsetY = (rcParent.top + rcParent.bottom) / 2 - (rectUnion.top + rectUnion.bottom) / 2;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);

		SIZE szXY = pControl->GetFixedXY();
		szXY.cy += nOffsetY;
		pControl->SetFixedXY(szXY);
	}

	pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignCenterHorizontally(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	CControlUI* pParent = pFocused->GetParent();
	if (!pParent)
		return;

	RECT rcParent = pParent->GetPos();

	CRect rectUnion;
	rectUnion.SetRectEmpty();
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pParent)
		{
			arrSelected.RemoveAt(i);
			continue;
		}

		rectUnion.UnionRect(&rectUnion, &pControl->GetPos());
	}

	int nOffsetX = (rcParent.left + rcParent.right) / 2 - (rectUnion.left + rectUnion.right) / 2;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);

		SIZE szXY = pControl->GetFixedXY();
		szXY.cx += nOffsetX;
		pControl->SetFixedXY(szXY);
	}

	pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignHorizontal(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	CControlUI* pParent = pFocused->GetParent();
	if (!pParent)
		return;

	CRect rectUnion;
	rectUnion.SetRectEmpty();
	int nTotalWidth = 0;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pParent)
		{
			arrSelected.RemoveAt(i);
			continue;
		}
		nTotalWidth += pControl->GetWidth();
		rectUnion.UnionRect(&rectUnion, &pControl->GetPos());
	}

	int nCount = arrSelected.GetSize();
	if (nCount < 3)
		return;
	int nSpaceX = (rectUnion.Width() - nTotalWidth) / (nCount - 1);
	int nMin;
	for (int i = 0; i < nCount - 1; i++)
	{
		nMin = i;
		int j;
		for (j = i + 1; j < nCount; j++)
		{
			if (arrSelected[j]->GetX() < arrSelected[nMin]->GetX())
				nMin = j;
		}
		if (i != nMin)
		{
			CControlUI* pControl = arrSelected[i];
			arrSelected[i] = arrSelected[nMin];
			arrSelected[nMin] = pControl;
		}
	}

	for (int i = 1; i < nCount - 1; i++)
	{
		int right = arrSelected[i - 1]->GetFixedXY().cx + arrSelected[i - 1]->GetWidth();
		SIZE szXY = arrSelected[i]->GetFixedXY();
		szXY.cx = right + nSpaceX;
		arrSelected[i]->SetFixedXY(szXY);
	}

	pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignVertical(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	CControlUI* pParent = pFocused->GetParent();
	if (!pParent)
		return;

	CRect rectUnion;
	rectUnion.SetRectEmpty();
	int nTotalHeight = 0;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl->GetParent() != pParent)
		{
			arrSelected.RemoveAt(i);
			continue;
		}
		nTotalHeight += pControl->GetHeight();
		rectUnion.UnionRect(&rectUnion, &pControl->GetPos());
	}

	int nCount = arrSelected.GetSize();
	if (nCount < 3)
		return;
	int nSpaceY = (rectUnion.Height() - nTotalHeight) / (nCount - 1);
	int nMin;
	for (int i = 0; i < nCount - 1; i++)
	{
		nMin = i;
		int j;
		for (j = i + 1; j < nCount; j++)
		{
			if (arrSelected[j]->GetY() < arrSelected[nMin]->GetY())
				nMin = j;
		}
		if (i != nMin)
		{
			CControlUI* pControl = arrSelected[i];
			arrSelected[i] = arrSelected[nMin];
			arrSelected[nMin] = pControl;
		}
	}

	for (int i = 1; i < nCount - 1; i++)
	{
		int bottom = arrSelected[i - 1]->GetFixedXY().cy + arrSelected[i - 1]->GetHeight();
		SIZE szXY = arrSelected[i]->GetFixedXY();
		szXY.cy = bottom + nSpaceY;
		arrSelected[i]->SetFixedXY(szXY);
	}

	pParent->SetPos(pParent->GetPos());
}

void CLayoutManager::AlignSameWidth(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	int nWidth = pFocused->GetFixedWidth();

	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl == pFocused)
			continue;

		pControl->SetFixedWidth(nWidth);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::AlignSameHeight(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	int nHeight = pFocused->GetFixedHeight();

	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl == pFocused)
			continue;

		pControl->SetFixedHeight(nHeight);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::AlignSameSize(CControlUI* pFocused, CArray<CControlUI*, CControlUI*>& arrSelected)
{
	int nWidth = pFocused->GetFixedWidth();
	int nHeight = pFocused->GetFixedHeight();

	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);
		if (pControl == pFocused)
			continue;

		pControl->SetFixedWidth(nWidth);
		pControl->SetFixedHeight(nHeight);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::ShowGrid(bool bShow)
{
	m_bShowGrid = bShow;
}

bool CLayoutManager::IsShowGrid() const
{
	return m_bShowGrid;
}

void CLayoutManager::ShowAuxBorder(bool bShow)
{
	m_bShowAuxBorder = bShow;
}

bool CLayoutManager::IsShowAuxBorder() const
{
	return m_bShowAuxBorder;
}

void CLayoutManager::MicoMoveUp(CArray<CControlUI*, CControlUI*>& arrSelected, int nMoved)
{
	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);

		SIZE szXY = pControl->GetFixedXY();
		szXY.cy -= nMoved;
		pControl->SetFixedXY(szXY);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::MicoMoveDown(CArray<CControlUI*, CControlUI*>& arrSelected, int nMoved)
{
	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);

		SIZE szXY = pControl->GetFixedXY();
		szXY.cy += nMoved;
		pControl->SetFixedXY(szXY);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::MicoMoveLeft(CArray<CControlUI*, CControlUI*>& arrSelected, int nMoved)
{
	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);

		SIZE szXY = pControl->GetFixedXY();
		szXY.cx -= nMoved;
		pControl->SetFixedXY(szXY);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::MicoMoveRight(CArray<CControlUI*, CControlUI*>& arrSelected, int nMoved)
{
	CDelayRepos DelayPos;
	for (int i = 0; i < arrSelected.GetSize(); i++)
	{
		CControlUI* pControl = arrSelected.GetAt(i);

		SIZE szXY = pControl->GetFixedXY();
		szXY.cx += nMoved;
		pControl->SetFixedXY(szXY);
		DelayPos.AddParent(pControl->GetParent());
	}
	DelayPos.Repos();
}

void CLayoutManager::SaveControlProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pControl->GetName() && _tcslen(pControl->GetName()) > 0)
	{
		CString strUIName = pControl->GetName();
		if (strUIName.Find(pControl->GetClass()) != 0)
		{
			pNode->SetAttribute("name", StringConvertor::WideToUtf8(pControl->GetName()));
		}
	}

	if (pControl->GetText() && _tcslen(pControl->GetText()) > 0)
		pNode->SetAttribute("text", StringConvertor::WideToUtf8(pControl->GetText()));

	if (pControl->GetToolTip() && _tcslen(pControl->GetToolTip()) > 0)
		pNode->SetAttribute("tooltip", StringConvertor::WideToUtf8(pControl->GetToolTip()));

	if (!pControl->IsVisible() && !((static_cast<IContainerUI*>(pControl->GetInterface(_T("IContainer"))) != NULL) && (static_cast<CContainerUI*>(pControl->GetInterface(_T("Container"))) != NULL)))
	{
		CControlUI* pParent = pControl->GetParent();
		if ((pParent != NULL) && ((static_cast<IContainerUI*>(pParent->GetInterface(_T("IContainer"))) != NULL) && (static_cast<CContainerUI*>(pParent->GetInterface(_T("Container"))) != NULL)))
		{
			// 如果同一层中所有元素都是不可见的，则不设置属性
			bool bVisible = false;
			CContainerUI* pContainerUI = static_cast<CContainerUI*>(pParent->GetInterface(_T("Container")));
			for (int it = 0; it < pContainerUI->GetCount(); it++)
			{
				CControlUI* pControl = static_cast<CControlUI*>(pContainerUI->GetItemAt(it));
				bVisible = pControl->IsVisible();
				if (bVisible)
					break;
			}
			if (bVisible)
				pNode->SetAttribute("visible", "false");
		}
	}

	if (pControl->GetShortcut() != _T('\0'))
	{
		_stprintf_s(szBuf, _T("%c"), pControl->GetShortcut());
		pNode->SetAttribute("shortcut", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetBorderSize() > 0)
	{
		_stprintf_s(szBuf, _T("%d"), pControl->GetBorderSize());
		pNode->SetAttribute("bordersize", StringConvertor::WideToUtf8(szBuf));
	}

#if 0
	if(pControl->IsFloat())
	{
		pNode->SetAttribute("float", "true");

		_stprintf_s(szBuf,
			_T("%d,%d,%d,%d"),
			pControl->GetFixedXY().cx,
			pControl->GetFixedXY().cy,
			pControl->GetFixedXY().cx + pControl->GetFixedWidth(),
			pControl->GetFixedXY().cy + pControl->GetFixedHeight()
			);
		pNode->SetAttribute("pos", StringConvertor::WideToUtf8(szBuf));
	}
	else
	{
		if((pControl->GetFixedXY().cx != 0)
			|| (pControl->GetFixedXY().cy != 0)
			|| (pControl->GetFixedWidth() != 0)
			|| (pControl->GetFixedHeight() != 0))
		{
			_stprintf_s(szBuf, _T("%d,%d,%d,%d"), pControl->GetFixedXY().cx, pControl->GetFixedXY().cy, pControl->GetFixedXY().cx + pControl->GetFixedWidth(), pControl->GetFixedXY().cy + pControl->GetFixedHeight());
			pNode->SetAttribute("pos", StringConvertor::WideToUtf8(szBuf));
		}

		if(pControl->GetFixedWidth() > 0)
		{
			_stprintf_s(szBuf, _T("%d"), pControl->GetFixedWidth());
			pNode->SetAttribute("width", StringConvertor::WideToUtf8(szBuf));
		}

		if(pControl->GetFixedHeight() > 0)
		{
			_stprintf_s(szBuf, _T("%d"), pControl->GetFixedHeight());
			pNode->SetAttribute("height", StringConvertor::WideToUtf8(szBuf));
		}
	}
#endif // 0

	// 在绝对坐标下输出pos坐标，使用前两个值表示坐标
	// 始终输出width和height来表示控件大小
	if (pControl->IsFloat())
	{
		//绝对位置(float = true)
		pNode->SetAttribute("float", "true");

		_stprintf_s(szBuf
			, _T("%d,%d,%d,%d")
			, pControl->GetFixedXY().cx
			, pControl->GetFixedXY().cy
			, 0//pControl->GetFixedXY().cx + pControl->GetFixedWidth(),
			, 0//pControl->GetFixedXY().cy + pControl->GetFixedHeight()
			);
		pNode->SetAttribute("pos", StringConvertor::WideToUtf8(szBuf));

		int fixed_w = pControl->GetFixedWidth();
		int fixed_h = pControl->GetFixedHeight();
		if (fixed_w > 0)
		{
			_stprintf_s(szBuf, _T("%d"), fixed_w);
			pNode->SetAttribute("width", StringConvertor::WideToUtf8(szBuf));
		}

		if (fixed_h > 0)
		{
			_stprintf_s(szBuf, _T("%d"), fixed_h);
			pNode->SetAttribute("height", StringConvertor::WideToUtf8(szBuf));
		}
	}
	else
	{
		//相对位置(float = false )
		CControlUI* pParent = pControl->GetParent();
		if (pParent)
		{
			CVerticalLayoutUI* pParentVLaout = static_cast<CVerticalLayoutUI*>(pParent->GetInterface(DUI_CTR_VERTICALLAYOUT));
			CHorizontalLayoutUI* pParentHLaout = static_cast<CHorizontalLayoutUI*>(pParent->GetInterface(DUI_CTR_HORIZONTALLAYOUT));

			int fixed_w = pControl->GetFixedWidth();
			int fixed_h = pControl->GetFixedHeight();
			if (pParentHLaout)
			{
				//设置"宽度"属性
				if (fixed_w > 0)
				{
					_stprintf_s(szBuf, _T("%d"), fixed_w);
					pNode->SetAttribute("width", StringConvertor::WideToUtf8(szBuf));
				}

				//移除多余"高度"属性
				pNode->RemoveAttribute("height");
			}
			else if (pParentVLaout)
			{
				//设置"高度"属性
				if (fixed_h > 0)
				{
					_stprintf_s(szBuf, _T("%d"), fixed_h);
					pNode->SetAttribute("height", StringConvertor::WideToUtf8(szBuf));
				}

				//移除多余"宽度"属性
				pNode->RemoveAttribute("width");
			}
			else
			{
				//设置"宽度"属性
				if (fixed_w > 0)
				{
					_stprintf_s(szBuf, _T("%d"), fixed_w);
					pNode->SetAttribute("width", StringConvertor::WideToUtf8(szBuf));
				}

				//设置"高度"属性
				if (fixed_h > 0)
				{
					_stprintf_s(szBuf, _T("%d"), fixed_h);
					pNode->SetAttribute("height", StringConvertor::WideToUtf8(szBuf));
				}
			}
		}
	}

	RECT rcPadding = pControl->GetPadding();
	if ((rcPadding.left != 0) || (rcPadding.right != 0) || (rcPadding.bottom != 0) || (rcPadding.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcPadding.left, rcPadding.top, rcPadding.right, rcPadding.bottom);
		pNode->SetAttribute("padding", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetBkImage() && _tcslen(pControl->GetBkImage()) > 0)
	{
		pNode->SetAttribute("bkimage", StringConvertor::WideToUtf8(ConvertImageFileName(pControl->GetBkImage())));
	}

	if (pControl->GetBkColor() != 0)
	{
		DWORD dwColor = pControl->GetBkColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("bkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetBkColor2() != 0)
	{
		DWORD dwColor = pControl->GetBkColor2();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));

		pNode->SetAttribute("bkcolor2", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetBorderColor() != 0)
	{
		DWORD dwColor = pControl->GetBorderColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("bordercolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetFocusBorderColor() != 0)
	{
		DWORD dwColor = pControl->GetFocusBorderColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("focusbordercolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetMaxHeight() != 9999)
	{
		_stprintf_s(szBuf, _T("%d"), pControl->GetMaxHeight());
		pNode->SetAttribute("maxheight", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetMaxWidth() != 9999)
	{
		_stprintf_s(szBuf, _T("%d"), pControl->GetMaxWidth());
		pNode->SetAttribute("maxwidth", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetMinWidth() != 0)
	{
		_stprintf_s(szBuf, _T("%d"), pControl->GetMinWidth());
		pNode->SetAttribute("minwidth", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->GetMinHeight() != 0)
	{
		_stprintf_s(szBuf, _T("%d"), pControl->GetMinHeight());
		pNode->SetAttribute("minheight", StringConvertor::WideToUtf8(szBuf));
	}

	TRelativePosUI relativePos = pControl->GetRelativePos();
	if (relativePos.bRelative)
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), relativePos.nMoveXPercent, relativePos.nMoveYPercent, relativePos.nZoomXPercent, relativePos.nZoomYPercent);
		pNode->SetAttribute("relativepos", StringConvertor::WideToUtf8(szBuf));
	}

	if (pControl->IsMouseEnabled() == false)
	{
		pNode->SetAttribute("mouse", "false");
	}

	if (pControl->IsTabEnable() == true)
	{
		pNode->SetAttribute("tab", "true");
	}

	if (pControl->IsContextMenuUsed())
	{
		pNode->SetAttribute("menu", "true");
	}

	if (!pControl->IsVisible())
	{
		pNode->SetAttribute("visible", "false");
	}
}

void CLayoutManager::SaveLabelProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);

	CLabelUI* pLabelUI = static_cast<CLabelUI*>(pControl->GetInterface(_T("Label")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	RECT rcTextPadding = pLabelUI->GetTextPadding();
	if ((rcTextPadding.left != 0) || (rcTextPadding.right != 0) || (rcTextPadding.bottom != 0) || (rcTextPadding.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcTextPadding.left, rcTextPadding.top, rcTextPadding.right, rcTextPadding.bottom);
		pNode->SetAttribute("textpadding", StringConvertor::WideToUtf8(szBuf));
	}

	DWORD iTextColor = pLabelUI->GetTextColor();
	if (iTextColor != 0x00000000 && iTextColor != 0xFF000000)
	{
		DWORD dwColor = pLabelUI->GetTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("textcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pLabelUI->GetDisabledTextColor() != 0xFFA7A6AA)
	{
		DWORD dwColor = pLabelUI->GetDisabledTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("disabledtextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	int nFont = pLabelUI->GetFont();
	if (nFont != -1)
		pNode->SetAttribute("font", nFont);

	if (pLabelUI->IsShowHtml())
		pNode->SetAttribute("showhtml", "true");

	CDuiString sAlign = pLabelUI->GetAlign();
	if (!sAlign.IsEmpty() && _tcscmp(sAlign, _T("left")) != 0)
		pNode->SetAttribute("align", StringConvertor::WideToUtf8(sAlign));

	if (pLabelUI->GetTextStyle() & DT_END_ELLIPSIS)
		pNode->SetAttribute("endellipsis", "true");
}

void CLayoutManager::SaveButtonProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveLabelProperty(pControl, pNode);
	TCHAR szBuf[MAX_PATH] = { 0 };

	CButtonUI* pButtonUI = static_cast<CButtonUI*>(pControl->GetInterface(_T("Button")));
	if (pButtonUI->GetNormalImage() && _tcslen(pButtonUI->GetNormalImage()) > 0)
		pNode->SetAttribute("normalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pButtonUI->GetNormalImage())));

	if (pButtonUI->GetHotImage() && _tcslen(pButtonUI->GetHotImage()) > 0)
		pNode->SetAttribute("hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pButtonUI->GetHotImage())));

	if (pButtonUI->GetPushedImage() && _tcslen(pButtonUI->GetPushedImage()) > 0)
		pNode->SetAttribute("pushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pButtonUI->GetPushedImage())));

	if (pButtonUI->GetFocusedImage() && _tcslen(pButtonUI->GetFocusedImage()) > 0)
		pNode->SetAttribute("focusedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pButtonUI->GetFocusedImage())));

	if (pButtonUI->GetDisabledImage() && _tcslen(pButtonUI->GetDisabledImage()) > 0)
		pNode->SetAttribute("disabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pButtonUI->GetDisabledImage())));

	if (pButtonUI->GetForeImage() && _tcslen(pButtonUI->GetForeImage()) > 0)
		pNode->SetAttribute("foreimage", StringConvertor::WideToUtf8(ConvertImageFileName(pButtonUI->GetForeImage())));

	if (pButtonUI->GetHotBkColor() != 0)
	{
		DWORD dwColor = pButtonUI->GetHotBkColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("hotbkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pButtonUI->GetFocusedTextColor() != 0)
	{
		DWORD dwColor = pButtonUI->GetFocusedTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("focusedtextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pButtonUI->GetPushedTextColor() != 0)
	{
		DWORD dwColor = pButtonUI->GetPushedTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("pushedtextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pButtonUI->GetHotTextColor() != 0)
	{
		DWORD dwColor = pButtonUI->GetHotTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("hottextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (!pButtonUI->IsKeyboardEnabled())
	{
		pNode->SetAttribute("keyboard", "false");
	}
}

void CLayoutManager::SaveOptionProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveButtonProperty(pControl, pNode);
	COptionUI* pOptionUI = static_cast<COptionUI*>(pControl->GetInterface(_T("Option")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pOptionUI->GetGroup() && _tcslen(pOptionUI->GetGroup()))
		pNode->SetAttribute("group", StringConvertor::WideToUtf8(pOptionUI->GetGroup()));

	if (pOptionUI->IsSelected())
		pNode->SetAttribute("selected", pOptionUI->IsSelected() ? "true" : "false");

	if (pOptionUI->GetForeImage() && _tcslen(pOptionUI->GetForeImage()) > 0)
		pNode->SetAttribute("foreimage", StringConvertor::WideToUtf8(ConvertImageFileName(pOptionUI->GetForeImage())));

	if (pOptionUI->GetSelectedImage() && _tcslen(pOptionUI->GetSelectedImage()) > 0)
		pNode->SetAttribute("selectedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pOptionUI->GetSelectedImage())));
}

void CLayoutManager::SaveProgressProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveLabelProperty(pControl, pNode);
	CProgressUI* pProgressUI = static_cast<CProgressUI*>(pControl->GetInterface(_T("Progress")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pProgressUI->GetForeImage() && _tcslen(pProgressUI->GetForeImage()) > 0)
		pNode->SetAttribute("foreimage", StringConvertor::WideToUtf8(ConvertImageFileName(pProgressUI->GetForeImage())));

	_stprintf_s(szBuf, _T("%d"), pProgressUI->GetMinValue());
	pNode->SetAttribute("min", StringConvertor::WideToUtf8(szBuf));


	_stprintf_s(szBuf, _T("%d"), pProgressUI->GetMaxValue());
	pNode->SetAttribute("max", StringConvertor::WideToUtf8(szBuf));

	_stprintf_s(szBuf, _T("%d"), pProgressUI->GetValue());
	pNode->SetAttribute("value", StringConvertor::WideToUtf8(szBuf));

	if (pProgressUI->IsHorizontal())
		pNode->SetAttribute("hor", pProgressUI->IsHorizontal() ? "true" : "false");

	if (!pProgressUI->IsStretchForeImage())
		pNode->SetAttribute("isstretchfore", pProgressUI->IsStretchForeImage() ? "true" : "false");
}

void CLayoutManager::SaveSliderProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveProgressProperty(pControl, pNode);

	CSliderUI* pSliderUI = static_cast<CSliderUI*>(pControl->GetInterface(_T("Slider")));
	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pSliderUI->GetThumbImage() && _tcslen(pSliderUI->GetThumbImage()) > 0)
		pNode->SetAttribute("thumbimage", StringConvertor::WideToUtf8(ConvertImageFileName(pSliderUI->GetThumbImage())));

	if (pSliderUI->GetThumbHotImage() && _tcslen(pSliderUI->GetThumbHotImage()) > 0)
		pNode->SetAttribute("thumbhotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pSliderUI->GetThumbHotImage())));

	if (pSliderUI->GetThumbPushedImage() && _tcslen(pSliderUI->GetThumbPushedImage()) > 0)
		pNode->SetAttribute("thumbpushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pSliderUI->GetThumbPushedImage())));

	_stprintf_s(szBuf, _T("%d,%d"), pSliderUI->GetThumbRect().right - pSliderUI->GetThumbRect().left, pSliderUI->GetThumbRect().bottom - pSliderUI->GetThumbRect().top);
	pNode->SetAttribute("thumbsize", StringConvertor::WideToUtf8(szBuf));
}

void CLayoutManager::SaveEditProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	TCHAR szBuf[MAX_PATH] = { 0 };

	SaveLabelProperty(pControl, pNode);
	CEditUI* pEditUI = static_cast<CEditUI*>(pControl->GetInterface(_T("Edit")));

	if (pEditUI->IsPasswordMode())
		pNode->SetAttribute("password", "true");

	if (pEditUI->IsReadOnly())
		pNode->SetAttribute("readonly", "true");

	if (pEditUI->GetMaxChar() != 255)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d"), pEditUI->GetMaxChar());
		pNode->SetAttribute("maxchar", StringConvertor::WideToUtf8(szBuf));
	}

	if (pEditUI->GetNativeEditBkColor() != 0xFFFFFFFF)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		DWORD dwColor = pEditUI->GetNativeEditBkColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("nativebkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pEditUI->GetNormalImage() && _tcslen(pEditUI->GetNormalImage()) > 0)
		pNode->SetAttribute("normalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pEditUI->GetNormalImage())));

	if (pEditUI->GetHotImage() && _tcslen(pEditUI->GetHotImage()) > 0)
		pNode->SetAttribute("hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pEditUI->GetHotImage())));

	if (pEditUI->GetFocusedImage() && _tcslen(pEditUI->GetFocusedImage()) > 0)
		pNode->SetAttribute("focusedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pEditUI->GetFocusedImage())));

	if (pEditUI->GetDisabledImage() && _tcslen(pEditUI->GetDisabledImage()) > 0)
		pNode->SetAttribute("disabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pEditUI->GetDisabledImage())));
}

void CLayoutManager::SaveRichEditProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveContainerProperty(pControl, pNode);

	TCHAR szBuf[MAX_PATH] = { 0 };
	CRichEditUI* pRichEditUI = static_cast<CRichEditUI*>(pControl->GetInterface(_T("RichEdit")));
	LONG lTwhStyle = pRichEditUI->GetWinStyle();

	if (_tcslen(pRichEditUI->GetTipValue()))
		pNode->SetAttribute("tipvalue", StringConvertor::WideToUtf8(pRichEditUI->GetTipValue()));

	if (pRichEditUI->GetTipValueColor() != 0xFFBAC0C5)
	{
		DWORD dwColor = pRichEditUI->GetTipValueColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("tipvaluecolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pRichEditUI->GetFont() != -1)
		pNode->SetAttribute("font", pRichEditUI->GetFont());

	if (pRichEditUI->GetTextColor() != 0)
	{
		DWORD dwColor = pRichEditUI->GetTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("textcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pRichEditUI->GetLimitText() != DuiLib::cInitTextMax)
		pNode->SetAttribute("maxchar", pRichEditUI->GetLimitText());

	if (pRichEditUI->IsReadOnly())
		pNode->SetAttribute("readonly", "true");

	if (pRichEditUI->IsReadOnlyShowCaret())
		pNode->SetAttribute("readonlyshowcaret", "true");

	if (!pRichEditUI->IsCanPaste())
		pNode->SetAttribute("canpaste", "false");

	if (lTwhStyle & ES_PASSWORD)
		pNode->SetAttribute("password", "true");

	//align
	std::wstring tstrAlgin;
	if (lTwhStyle & ES_LEFT)
		tstrAlgin = _T("left");
	else if (lTwhStyle & ES_CENTER)
		tstrAlgin = _T("center");
	else if (lTwhStyle & ES_RIGHT)
		tstrAlgin = _T("right");
	if (!tstrAlgin.empty())
		pNode->SetAttribute("align", StringConvertor::WideToUtf8(tstrAlgin.c_str()));

	//else
	if (lTwhStyle & ES_MULTILINE)
		pNode->SetAttribute("multiline", "true");

	if (pRichEditUI->IsRich())
		pNode->SetAttribute("rich", "true");

	if (pRichEditUI->IsWantTab())
		pNode->SetAttribute("wanttab", "true");

	if (pRichEditUI->IsWantReturn())
		pNode->SetAttribute("wantreturn", "true");

	if (pRichEditUI->IsWantCtrlReturn())
		pNode->SetAttribute("wantctrlreturn", "true");

	if (lTwhStyle & (ES_DISABLENOSCROLL | WS_VSCROLL))
		pNode->SetAttribute("vscrollbar", "true");
	else
		pNode->RemoveAttribute("vscrollbar");

	if (lTwhStyle & (ES_DISABLENOSCROLL | WS_HSCROLL))
		pNode->SetAttribute("hscrollbar", "true");
	else
		pNode->RemoveAttribute("hscrollbar");

	if (lTwhStyle & ES_AUTOVSCROLL)
		pNode->SetAttribute("autovscroll", "true");
	else
		pNode->RemoveAttribute("autovscroll");

	if (lTwhStyle & ES_AUTOHSCROLL)
		pNode->SetAttribute("autohscroll", "true");
	else
		pNode->RemoveAttribute("autohscroll");

	if (_tcslen(pRichEditUI->GetNormalImage()) > 0)
		pNode->SetAttribute("normalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pRichEditUI->GetNormalImage())));

	if (_tcslen(pRichEditUI->GetHotImage()) > 0)
		pNode->SetAttribute("hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pRichEditUI->GetHotImage())));

	if (_tcslen(pRichEditUI->GetFocusedImage()) > 0)
		pNode->SetAttribute("focusedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pRichEditUI->GetFocusedImage())));

	if (_tcslen(pRichEditUI->GetDisabledImage()) > 0)
		pNode->SetAttribute("disabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pRichEditUI->GetDisabledImage())));

	RECT rcTextPadding = pRichEditUI->GetTextPadding();
	if ((rcTextPadding.left != 0) || (rcTextPadding.right != 0) || (rcTextPadding.bottom != 0) || (rcTextPadding.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcTextPadding.left, rcTextPadding.top, rcTextPadding.right, rcTextPadding.bottom);
		pNode->SetAttribute("textpadding", StringConvertor::WideToUtf8(szBuf));
	}
}

void CLayoutManager::SaveScrollBarProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);
	CScrollBarUI* pScrollbarUI = static_cast<CScrollBarUI*>(pControl->GetInterface(DUI_CTR_SCROLLBAR));
	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pScrollbarUI->GetButton1NormalImage() && _tcslen(pScrollbarUI->GetButton1NormalImage()) > 0)
		pNode->SetAttribute("button1normalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton1NormalImage())));
	if (pScrollbarUI->GetButton1HotImage() && _tcslen(pScrollbarUI->GetButton1HotImage()) > 0)
		pNode->SetAttribute("button1hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton1HotImage())));
	if (pScrollbarUI->GetButton1PushedImage() && _tcslen(pScrollbarUI->GetButton1PushedImage()) > 0)
		pNode->SetAttribute("button1pushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton1PushedImage())));
	if (pScrollbarUI->GetButton1DisabledImage() && _tcslen(pScrollbarUI->GetButton1DisabledImage()) > 0)
		pNode->SetAttribute("button1disabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton1DisabledImage())));

	if (pScrollbarUI->GetButton2NormalImage() && _tcslen(pScrollbarUI->GetButton2NormalImage()) > 0)
		pNode->SetAttribute("button2normalimage", StringConvertor::WideToUtf8((pScrollbarUI->GetButton2NormalImage())));
	if (pScrollbarUI->GetButton2HotImage() && _tcslen(pScrollbarUI->GetButton2HotImage()) > 0)
		pNode->SetAttribute("button2hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton2HotImage())));
	if (pScrollbarUI->GetButton2PushedImage() && _tcslen(pScrollbarUI->GetButton2PushedImage()) > 0)
		pNode->SetAttribute("button2pushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton2PushedImage())));
	if (pScrollbarUI->GetButton2DisabledImage() && _tcslen(pScrollbarUI->GetButton2DisabledImage()) > 0)
		pNode->SetAttribute("button2disabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetButton2DisabledImage())));

	if (pScrollbarUI->GetThumbNormalImage() && _tcslen(pScrollbarUI->GetThumbNormalImage()) > 0)
		pNode->SetAttribute("thumbnormalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetThumbNormalImage())));
	if (pScrollbarUI->GetThumbHotImage() && _tcslen(pScrollbarUI->GetThumbHotImage()) > 0)
		pNode->SetAttribute("thumbhotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetThumbHotImage())));
	if (pScrollbarUI->GetThumbPushedImage() && _tcslen(pScrollbarUI->GetThumbPushedImage()) > 0)
		pNode->SetAttribute("thumbpushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetThumbPushedImage())));
	if (pScrollbarUI->GetThumbDisabledImage() && _tcslen(pScrollbarUI->GetThumbDisabledImage()) > 0)
		pNode->SetAttribute("thumbdisabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetThumbDisabledImage())));

	if (pScrollbarUI->GetRailNormalImage() && _tcslen(pScrollbarUI->GetRailNormalImage()) > 0)
		pNode->SetAttribute("railnormalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetRailNormalImage())));
	if (pScrollbarUI->GetRailHotImage() && _tcslen(pScrollbarUI->GetRailHotImage()) > 0)
		pNode->SetAttribute("railhotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetRailHotImage())));
	if (pScrollbarUI->GetRailPushedImage() && _tcslen(pScrollbarUI->GetRailPushedImage()) > 0)
		pNode->SetAttribute("railpushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetRailPushedImage())));
	if (pScrollbarUI->GetRailDisabledImage() && _tcslen(pScrollbarUI->GetRailDisabledImage()) > 0)
		pNode->SetAttribute("raildisabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetRailDisabledImage())));

	if (pScrollbarUI->GetBkNormalImage() && _tcslen(pScrollbarUI->GetBkNormalImage()) > 0)
		pNode->SetAttribute("bknormalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetBkNormalImage())));
	if (pScrollbarUI->GetBkHotImage() && _tcslen(pScrollbarUI->GetBkHotImage()) > 0)
		pNode->SetAttribute("bkhotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetBkHotImage())));
	if (pScrollbarUI->GetBkPushedImage() && _tcslen(pScrollbarUI->GetBkPushedImage()) > 0)
		pNode->SetAttribute("bkpushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetBkPushedImage())));
	if (pScrollbarUI->GetBkDisabledImage() && _tcslen(pScrollbarUI->GetBkDisabledImage()) > 0)
		pNode->SetAttribute("bkdisabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pScrollbarUI->GetBkDisabledImage())));

	_stprintf_s(szBuf, _T("%d"), pScrollbarUI->GetLineSize());
	pNode->SetAttribute("linesize", StringConvertor::WideToUtf8(szBuf));

	_stprintf_s(szBuf, _T("%d"), pScrollbarUI->GetScrollRange());
	pNode->SetAttribute("range", StringConvertor::WideToUtf8(szBuf));

	_stprintf_s(szBuf, _T("%d"), pScrollbarUI->GetScrollPos());
	pNode->SetAttribute("value", StringConvertor::WideToUtf8(szBuf));

	if (pScrollbarUI->IsHorizontal())
		pNode->SetAttribute("hor", pScrollbarUI->IsHorizontal() ? "true" : "false");
}

void CLayoutManager::SaveListProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);
	SaveItemProperty(pControl, pNode);

	CListUI* pListUI = static_cast<CListUI*>(pControl->GetInterface(_T("List")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pListUI->GetHeader() && !pListUI->GetHeader()->IsVisible())
		pNode->SetAttribute("header", "hidden");

	if (pListUI->GetHeader() && pListUI->GetHeader()->GetBkImage() && _tcslen(pListUI->GetHeader()->GetBkImage()) > 0)
		pNode->SetAttribute("headerbkimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListUI->GetHeader()->GetBkImage())));

	if (pListUI->IsItemShowHtml())
		pNode->SetAttribute("itemshowhtml", pListUI->IsItemShowHtml() ? "true" : "false");

	CContainerUI* pContainerUI = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));
	RECT rcInset = pContainerUI->GetInset();
	if ((rcInset.left != 0) || (rcInset.right != 0) || (rcInset.bottom != 0) || (rcInset.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcInset.left, rcInset.top, rcInset.right, rcInset.bottom);
		pNode->SetAttribute("inset", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListUI->GetVerticalScrollBar())
		pNode->SetAttribute("vscrollbar", "true");

	if (pListUI->GetHorizontalScrollBar())
		pNode->SetAttribute("hscrollbar", "true");

	if (pListUI->GetHeader())
	{
		CContainerUI* pContainerUI = static_cast<CContainerUI*>(pListUI->GetHeader());
		SaveProperties(pContainerUI, pNode);
	}
}

void CLayoutManager::SaveComboProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveContainerProperty(pControl, pNode);
	SaveItemProperty(pControl, pNode);

	CComboUI* pComboUI = static_cast<CComboUI*>(pControl->GetInterface(_T("Combo")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pComboUI->GetNormalImage() && _tcslen(pComboUI->GetNormalImage()) > 0)
		pNode->SetAttribute("normalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pComboUI->GetNormalImage())));

	if (pComboUI->GetHotImage() && _tcslen(pComboUI->GetHotImage()) > 0)
		pNode->SetAttribute("hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pComboUI->GetHotImage())));

	if (pComboUI->GetPushedImage() && _tcslen(pComboUI->GetPushedImage()) > 0)
		pNode->SetAttribute("pushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pComboUI->GetPushedImage())));

	if (pComboUI->GetFocusedImage() && _tcslen(pComboUI->GetFocusedImage()) > 0)
		pNode->SetAttribute("focusedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pComboUI->GetFocusedImage())));

	if (pComboUI->GetDisabledImage() && _tcslen(pComboUI->GetDisabledImage()) > 0)
		pNode->SetAttribute("disabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pComboUI->GetDisabledImage())));

	if ((pComboUI->GetDropBoxSize().cx != 0) || (pComboUI->GetDropBoxSize().cy != 150))
	{
		_stprintf_s(szBuf, _T("%d,%d"), pComboUI->GetDropBoxSize().cx, pComboUI->GetDropBoxSize().cy);
		pNode->SetAttribute("dropboxsize", StringConvertor::WideToUtf8(szBuf));
	}

	if (pComboUI->IsItemShowHtml())
		pNode->SetAttribute("itemshowhtml", pComboUI->IsItemShowHtml() ? "true" : "false");

	CContainerUI* pContainerUI = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));
	RECT rcInset = pContainerUI->GetInset();
	if ((rcInset.left != 0) || (rcInset.right != 0) || (rcInset.bottom != 0) || (rcInset.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcInset.left, rcInset.top, rcInset.right, rcInset.bottom);
		pNode->SetAttribute("inset", StringConvertor::WideToUtf8(szBuf));
	}
}

void CLayoutManager::SaveListHeaderItemProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);

	CListHeaderItemUI* pListHeaderItemUI = static_cast<CListHeaderItemUI*>(pControl->GetInterface(_T("ListHeaderItem")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	if (pListHeaderItemUI->GetTextColor() != 0)
	{
		DWORD dwColor = pListHeaderItemUI->GetTextColor();
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("textcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListHeaderItemUI->GetSepWidth() != 0)
	{
		_stprintf_s(szBuf, _T("%d"), pListHeaderItemUI->GetSepWidth());
		pNode->SetAttribute("sepwidth", StringConvertor::WideToUtf8(szBuf));
	}

	if (!pListHeaderItemUI->IsDragable())
		pNode->SetAttribute("dragable", "false");

	std::wstring tstrAlgin;
	UINT uTextStyle = pListHeaderItemUI->GetTextStyle();

	if (uTextStyle & DT_LEFT)
		tstrAlgin = _T("left");

	if (uTextStyle & DT_CENTER)
		tstrAlgin = _T("center");

	if (uTextStyle & DT_RIGHT)
		tstrAlgin = _T("right");

	if (uTextStyle & DT_TOP)
		tstrAlgin += _T("top");

	if (uTextStyle & DT_BOTTOM)
		tstrAlgin += _T("bottom");

	if (uTextStyle & DT_WORDBREAK)
		tstrAlgin += _T("wrap");

	if (!tstrAlgin.empty())
		pNode->SetAttribute("align", StringConvertor::WideToUtf8(tstrAlgin.c_str()));

	if (pListHeaderItemUI->GetNormalImage() && _tcslen(pListHeaderItemUI->GetNormalImage()) > 0)
		pNode->SetAttribute("normalimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListHeaderItemUI->GetNormalImage())));

	if (pListHeaderItemUI->GetHotImage() && _tcslen(pListHeaderItemUI->GetHotImage()) > 0)
		pNode->SetAttribute("hotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListHeaderItemUI->GetHotImage())));

	if (pListHeaderItemUI->GetPushedImage() && _tcslen(pListHeaderItemUI->GetPushedImage()) > 0)
		pNode->SetAttribute("pushedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListHeaderItemUI->GetPushedImage())));

	if (pListHeaderItemUI->GetFocusedImage() && _tcslen(pListHeaderItemUI->GetFocusedImage()) > 0)
		pNode->SetAttribute("focusedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListHeaderItemUI->GetFocusedImage())));

	if (pListHeaderItemUI->GetSepImage() && _tcslen(pListHeaderItemUI->GetSepImage()) > 0)
		pNode->SetAttribute("sepimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListHeaderItemUI->GetSepImage())));
}

void CLayoutManager::SaveListElementProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);
}

void CLayoutManager::SaveContainerProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);
	CContainerUI* pContainerUI = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));

	TCHAR szBuf[MAX_PATH] = { 0 };

	//inset
	RECT rcInset = pContainerUI->GetInset();
	if ((rcInset.left != 0) || (rcInset.right != 0) || (rcInset.bottom != 0) || (rcInset.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcInset.left, rcInset.top, rcInset.right, rcInset.bottom);
		pNode->SetAttribute("inset", StringConvertor::WideToUtf8(szBuf));
	}

	//childpadding
	int nChildPadding = pContainerUI->GetChildPadding();
	if (nChildPadding > 0)
	{
		_stprintf_s(szBuf, _T("%d"), nChildPadding);
		pNode->SetAttribute("childpadding", StringConvertor::WideToUtf8(szBuf));
	}

	//mousechild
	if (!pContainerUI->IsMouseChildEnabled())
		pNode->SetAttribute("mousechild", "false");

	//vscrollbar
	if (pContainerUI->GetVerticalScrollBar())
		pNode->SetAttribute("vscrollbar", "true");

	//hscrollbar
	if (pContainerUI->GetHorizontalScrollBar())
		pNode->SetAttribute("hscrollbar", "true");
}

void CLayoutManager::SaveHorizontalLayoutProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveContainerProperty(pControl, pNode);
}

void CLayoutManager::SaveTileLayoutProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveContainerProperty(pControl, pNode);
}

void CLayoutManager::SaveActiveXProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);
	CActiveXUI* pActiveUI = static_cast<CActiveXUI*>(pControl->GetInterface(_T("ActiveX")));

	TCHAR szBuf[128] = { 0 };

	CLSID clsid = pActiveUI->GetClisd();
	if (clsid != IID_NULL)
	{
		StringFromGUID2(clsid, szBuf, 128);
		pNode->SetAttribute("clsid", StringConvertor::WideToUtf8(szBuf));
	}

	if (!pActiveUI->IsDelayCreate())
	{
		pNode->SetAttribute("delaycreate", "false");
	}

	if (pActiveUI->GetModuleName() && _tcslen(pActiveUI->GetModuleName()) > 0)
	{
		pNode->SetAttribute("modulename", StringConvertor::WideToUtf8(pActiveUI->GetModuleName()));
	}
}
void CLayoutManager::SaveListContainerElementProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveContainerProperty(pControl, pNode);
}

void CLayoutManager::SaveProperties(CControlUI* pControl, TiXmlElement* pParentNode
	, BOOL bSaveChildren/* = TRUE*/)
{
	if ((pControl == NULL) || (pParentNode == NULL))
		return;

	CString strClass = pControl->GetClass();

	//占位控件拦截, 节点名统一使用Control
	if (true)
	{
		CVerticalLayoutUI* pVerticalLayout = static_cast<CVerticalLayoutUI*>(pControl->GetInterface(DUI_CTR_VERTICALLAYOUT));
		CHorizontalLayoutUI* pHorizontalLayout = static_cast<CHorizontalLayoutUI*>(pControl->GetInterface(DUI_CTR_HORIZONTALLAYOUT));
		CContainerUI* pContainer = nullptr;
		if (pVerticalLayout)
			pContainer = pVerticalLayout;
		else if (pHorizontalLayout)
			pContainer = pHorizontalLayout;

		if (pContainer && pContainer->GetCount() <= 0)
		{
			//目的只是为了提取strClass类型,控件内容等保留
			pControl = dynamic_cast<CControlUI*>(pControl);
			if (pControl)
			{
				CControlUI* pcon = new CControlUI;
				strClass = pcon->GetClass();
				delete pcon;
				pcon = nullptr;
			}
		}
	}

	strClass = strClass.Mid(0, strClass.GetLength() - 2);
	TiXmlElement* pNode = new TiXmlElement(StringConvertor::WideToUtf8(strClass.GetBuffer()));
	CUserDefineUI* pUserDefinedControl = static_cast<CUserDefineUI*>(pControl->GetInterface(_T("UserDefinedControl")));
	if (pUserDefinedControl != NULL)
	{
		std::map<CDuiString, CDuiString>::iterator iter = pUserDefinedControl->m_pAttributeList.begin();
		for (; iter != pUserDefinedControl->m_pAttributeList.end(); iter++)
		{
			pNode->SetAttribute(StringConvertor::WideToUtf8(iter->first), StringConvertor::WideToUtf8(iter->second));
		}
	}

	ExtendedAttributes* pExtended = (ExtendedAttributes*)pControl->GetTag();

	ExtendedAttributes mDummy;
	if (pExtended == NULL)
	{
		pExtended = &mDummy;
		ZeroMemory(pExtended, sizeof(ExtendedAttributes));
		LPCTSTR pstrClass = pControl->GetClass();
		SIZE_T cchLen = _tcslen(pstrClass);
		switch (cchLen)
		{
			case 16:
				if (_tcscmp(_T("ListHeaderItemUI"), pstrClass) == 0) pExtended->nClass = classListHeaderItem;
				break;
			case 12:
				if (_tcscmp(_T("ListHeaderUI"), pstrClass) == 0) pExtended->nClass = classListHeader;
				break;
		}
	}

	switch (pExtended->nClass)
	{
		case classControl:
			SaveControlProperty(pControl, pNode);
			break;
		case classLabel:
		case classText:
			SaveLabelProperty(pControl, pNode);
			break;
		case classButton:
			SaveButtonProperty(pControl, pNode);
			break;
		case classEdit:
			SaveEditProperty(pControl, pNode);
			break;
		case classRichEdit:
			SaveRichEditProperty(pControl, pNode);
			break;
		case classOption:
			SaveOptionProperty(pControl, pNode);
			break;
		case classProgress:
			SaveProgressProperty(pControl, pNode);
			break;
		case classSlider:
			SaveSliderProperty(pControl, pNode);
			break;
		case classCombo:
			SaveComboProperty(pControl, pNode);
			break;
		case classList:
			SaveListProperty(pControl, pNode);
			break;
		case classListContainerElement:
			SaveListContainerElementProperty(pControl, pNode);
			break;
		case classListHeaderItem:
			SaveListHeaderItemProperty(pControl, pNode);
			break;
		case classActiveX:
			SaveActiveXProperty(pControl, pNode);
			break;
		case classListHeader:
			SaveListHeaderProperty(pControl, pNode);
			break;
		case classContainer:
		case classVerticalLayout:
			SaveContainerProperty(pControl, pNode);
			break;
		case classTabLayout:
			SaveTabLayoutProperty(pControl, pNode);
			break;
		case classHorizontalLayout:
			SaveHorizontalLayoutProperty(pControl, pNode);
			break;
		case classTileLayout:
			SaveTileLayoutProperty(pControl, pNode);
			break;
		case classChildLayout:
			SaveChildWindowProperty(pControl, pNode);
			break;
		case classWebBrowser:
			SaveWebBrowserProperty(pControl, pNode);
			break;
		case classScrollBar:
			SaveScrollBarProperty(pControl, pNode);
		default:
			break;
	}
	TiXmlNode* pNodeElement = pParentNode->InsertEndChild(*pNode);
	delete pNode;

	if (bSaveChildren == FALSE)
		return;

	CContainerUI* pContainer = static_cast<CContainerUI*>(pControl->GetInterface(_T("Container")));
	if (pContainer == NULL)
		return;
	for (int it = 0; it < pContainer->GetCount(); it++)
	{
		CControlUI* pControl = static_cast<CControlUI*>(pContainer->GetItemAt(it));
		SaveProperties(pControl, pNodeElement->ToElement());
	}
}

bool CLayoutManager::SaveSkinFile(LPCTSTR pstrPathName)
{
	ASSERT(m_pFormUI);

	CString strPathName(pstrPathName);
	int nPos = strPathName.ReverseFind(_T('\\'));
	if (nPos == -1) return false;
	m_strSkinDir = strPathName.Left(nPos + 1);

	TCHAR szBuf[MAX_PATH] = { 0 };
	TiXmlDocument xmlDoc(StringConvertor::WideToAnsi(pstrPathName));
	TiXmlDeclaration Declaration("1.0", "utf-8", "yes");
	xmlDoc.InsertEndChild(Declaration);

	TiXmlElement* pFormElm = new TiXmlElement("Window");

	SIZE szSize = m_pFormUI->GetInitSize();
	if (szSize.cx > 0 && szSize.cy > 0)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d,%d"), szSize.cx, szSize.cy);
		pFormElm->SetAttribute("size", StringConvertor::WideToUtf8(szBuf));
	}

	szSize = m_pFormUI->GetMinInfo();
	if ((szSize.cx != 0) || (szSize.cy != 0))
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d,%d"), szSize.cx, szSize.cy);
		pFormElm->SetAttribute("mininfo", StringConvertor::WideToUtf8(szBuf));
	}

	szSize = m_pFormUI->GetMaxInfo();
	if ((szSize.cx != 0) || (szSize.cy != 0))
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d,%d"), szSize.cx, szSize.cy);
		pFormElm->SetAttribute("maxinfo", StringConvertor::WideToUtf8(szBuf));
	}

	szSize = m_pFormUI->GetRoundCorner();
	if ((szSize.cx != 0) || (szSize.cy != 0))
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d,%d"), szSize.cx, szSize.cy);
		pFormElm->SetAttribute("roundcorner", StringConvertor::WideToUtf8(szBuf));
	}

	RECT reRect = m_pFormUI->GetSizeBox();
	if ((reRect.left != 0) || (reRect.right != 0) || (reRect.bottom != 0) || (reRect.top != 0))
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), reRect.left, reRect.top, reRect.right, reRect.bottom);
		pFormElm->SetAttribute("sizebox", StringConvertor::WideToUtf8(szBuf));
	}

	reRect = m_pFormUI->GetCaptionRect();
	if ((reRect.left != 0) || (reRect.right != 0) || (reRect.bottom != 0) || (reRect.top != 0))
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), reRect.left, reRect.top, reRect.right, reRect.bottom);
		pFormElm->SetAttribute("caption", StringConvertor::WideToUtf8(szBuf));
	}

	if (m_pFormUI->IsShowUpdateRect())
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_tcscpy(szBuf, _T("true"));
		pFormElm->SetAttribute("showdirty", StringConvertor::WideToUtf8(szBuf));
	}

	int iOpacity = m_pFormUI->GetAlpha();
	if (iOpacity != 255)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d"), iOpacity);
		pFormElm->SetAttribute("alpha", StringConvertor::WideToUtf8(szBuf));
	}

	bool bktrans = m_pFormUI->GetBackgroundTransparent();
	if (bktrans)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_tcscpy(szBuf, _T("true"));
		pFormElm->SetAttribute("bktrans", StringConvertor::WideToUtf8(szBuf));
	}

	DWORD dwColor = m_pFormUI->GetDefaultFontColor();
	if (dwColor != 0xFF000000)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pFormElm->SetAttribute("defaultfontcolor", StringConvertor::WideToUtf8(szBuf));
	}

	dwColor = m_pFormUI->GetDefaultSelectedFontColor();
	if (dwColor != 0xFFBAE4FF)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pFormElm->SetAttribute("selectedcolor", StringConvertor::WideToUtf8(szBuf));
	}

	dwColor = m_pFormUI->GetDefaultDisabledFontColor();
	if (dwColor != 0xFFA7A6AA)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pFormElm->SetAttribute("disabledfontcolor", StringConvertor::WideToUtf8(szBuf));
	}

	dwColor = m_pFormUI->GetDefaultLinkFontColor();
	if (dwColor != 0xFF0000FF)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pFormElm->SetAttribute("linkfontcolor", StringConvertor::WideToUtf8(szBuf));
	}

	dwColor = m_pFormUI->GetDefaultLinkHoverFontColor();
	if (dwColor != 0xFFD3215F)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pFormElm->SetAttribute("linkhoverfontcolor", StringConvertor::WideToUtf8(szBuf));
	}

	TiXmlNode* pNode = xmlDoc.InsertEndChild(*pFormElm);

	//默认字体管理
	CPaintManagerUI* pManager = m_pFormUI->GetManager();
	if (pManager->GetCustomFontCount() > 0)
	{
		TFontInfo* default_info = pManager->GetDefaultFontInfo();
		HFONT hDefaultFont = default_info->hFont;
		LOGFONT lfDefault = { 0 };
		GetObject(hDefaultFont, sizeof(LOGFONT), &lfDefault);

		std::vector<LOGFONT> cachedFonts;
		std::vector<INT> cachedFontsID;

		for (DWORD index = 0; index < pManager->GetCustomFontCount(); ++index)
		{
			HFONT hFont = pManager->GetFont(index);
			LOGFONT lf = { 0 };
			GetObject(hFont, sizeof(LOGFONT), &lf);

			bool bSaved = false;
			for (std::vector<LOGFONT>::const_iterator citer = cachedFonts.begin(); citer != cachedFonts.end(); ++citer)
			{
				if ((citer->lfWeight == lf.lfWeight) && (citer->lfItalic == lf.lfItalic) && (citer->lfHeight == lf.lfHeight)
					&& (_tcsicmp(lf.lfFaceName, citer->lfFaceName) == 0))
				{
					bSaved = true;
					break;
				}
			}
			if (bSaved)
				continue;

			cachedFonts.push_back(lf);

			TiXmlElement* pFontElem = new TiXmlElement("Font");

			_stprintf_s(szBuf, _T("%d"), index);
			pFontElem->SetAttribute("id", StringConvertor::WideToUtf8(szBuf));

			pFontElem->SetAttribute("name", StringConvertor::WideToUtf8(lf.lfFaceName));

			_stprintf_s(szBuf, _T("%d"), -lf.lfHeight);
			pFontElem->SetAttribute("size", StringConvertor::WideToUtf8(szBuf));

			pFontElem->SetAttribute("bold", (lf.lfWeight >= FW_BOLD) ? "true" : "false");
			pFontElem->SetAttribute("italic", lf.lfItalic ? "true" : "false");

			if ((lfDefault.lfWeight == lf.lfWeight) && (lfDefault.lfItalic == lf.lfItalic) && (lfDefault.lfHeight == lf.lfHeight)
				&& (_tcsicmp(lf.lfFaceName, lfDefault.lfFaceName) == 0))
				pFontElem->SetAttribute("default", "true");

			pNode->ToElement()->InsertEndChild(*pFontElem);

			delete pFontElem;
			pFontElem = NULL;
		}
	}

	//默认属性列表
	const CStdStringPtrMap& defaultAttrHash = pManager->GetDefaultAttribultes();
	if (defaultAttrHash.GetSize() > 0)
	{
		for (int index = 0; index < defaultAttrHash.GetSize(); ++index)
		{
			LPCTSTR lpstrKey = defaultAttrHash.GetAt(index);
			LPCTSTR lpstrAttribute = pManager->GetDefaultAttributeList(lpstrKey);

			TiXmlElement* pAttributeElem = new TiXmlElement("Default");
			pAttributeElem->SetAttribute("name", StringConvertor::WideToUtf8(lpstrKey));

			CString strAttrib(lpstrAttribute);
			pAttributeElem->SetAttribute("value", StringConvertor::WideToUtf8(strAttrib));

			pNode->ToElement()->InsertEndChild(*pAttributeElem);

			delete pAttributeElem;
			pAttributeElem = NULL;
		}
	}

	//保存子控件属性
	SaveProperties(m_pFormUI->GetItemAt(0), pNode->ToElement());

	delete pFormElm;
	return xmlDoc.SaveFile();
}

void CLayoutManager::SetDefaultUIName(CControlUI* pControl)
{
	m_Manager.ReapObjects(pControl);

	BOOL bNeedName = FALSE;
	CString strName = pControl->GetName();
	if (strName.IsEmpty())
		bNeedName = TRUE;
	else
	{
		if (m_Manager.FindControl(strName))
			bNeedName = TRUE;
		else
			m_Manager.InitControls(pControl);
	}
	if (!bNeedName)
		return;

	int nCount = 0;
	CString strUIName;
	do
	{
		nCount++;
		strUIName.Format(_T("%s%d"), pControl->GetClass(), nCount);
	} while (m_Manager.FindControl(strUIName));
	pControl->SetName(strUIName);
	m_Manager.InitControls(pControl);
}

CString CLayoutManager::ConvertImageFileName(LPCTSTR pstrImageAttrib)
{
	CString strImageAttrib(pstrImageAttrib);
	strImageAttrib.Replace(m_strSkinDir, _T(""));
	// 	CStdString sItem;
	// 	CStdString sValue;
	// 	LPTSTR pstr = (LPTSTR)pstrImageAttrib;
	// 	while( *pstr != _T('\0') )
	// 	{
	// 		sItem.Empty();
	// 		sValue.Empty();
	// 		while( *pstr != _T('\0') && *pstr != _T('=') )
	// 		{
	// 			LPTSTR pstrTemp = ::CharNext(pstr);
	// 			while( pstr < pstrTemp)
	// 			{
	// 				sItem += *pstr++;
	// 			}
	// 		}
	// 		if( *pstr++ != _T('=') ) break;
	// 		if( *pstr++ != _T('\'') ) break;
	// 		while( *pstr != _T('\0') && *pstr != _T('\'') )
	// 		{
	// 			LPTSTR pstrTemp = ::CharNext(pstr);
	// 			while( pstr < pstrTemp)
	// 			{
	// 				sValue += *pstr++;
	// 			}
	// 		}
	// 		if( *pstr++ != _T('\'') ) break;
	// 		if( !sValue.IsEmpty() ) {
	// 			if( sItem == _T("file"))
	// 				break;
	// 		}
	// 		if( *pstr++ != _T(' ') ) break;
	// 	}
	// 
	// 	if(sValue.IsEmpty())
	// 		sValue = sItem;
	// 	CString strFileName = sValue;
	// 	int nPos = strFileName.ReverseFind(_T('\\'));
	// 	if(nPos != -1)
	// 	{
	// 		strFileName = strFileName.Right(strFileName.GetLength() - nPos - 1);
	// 		strImageAttrib.Replace(sValue, strFileName);
	// 	}

	return strImageAttrib;
}

BOOL CLayoutManager::ConvertSurplusFileName(DuiLib::CDuiString& sTempPath, LPCTSTR& lpOutFileName, BOOL bShowBox /* = TRUE */)
{
	if (_tcscmp(lpOutFileName, _T("")) == 0)
		return FALSE;

	CDuiString resourcePath = CPaintManagerUI::GetResourcePath();
	if (!::PathIsDirectory(resourcePath.GetData())) return FALSE;

	TCHAR path[MAX_PATH] = { 0 };
	sTempPath = lpOutFileName;

	::PathCanonicalize(path, resourcePath.GetData());
	resourcePath = path;
	int iCount = sTempPath.Replace(resourcePath, _T(""));
	lpOutFileName = sTempPath.GetData();

	if (iCount > 0)
		return TRUE;

	if (bShowBox)
	{
		HWND hWnd = ::AfxGetMainWnd()->m_hWnd;
		MessageBox(hWnd, L"资源路径匹配错误!", L"caption", MB_OK);
	}

	return FALSE;
}

void CLayoutManager::SaveItemProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	IListOwnerUI* pList = static_cast<IListOwnerUI*>(pControl->GetInterface(_T("IListOwner")));
	TListInfoUI* pListInfo = pList->GetListInfo();
	TCHAR szBuf[MAX_PATH] = { 0 };

	RECT rcItemPadding = pListInfo->rcTextPadding;
	if ((rcItemPadding.left != 0) || (rcItemPadding.right != 0) || (rcItemPadding.bottom != 0) || (rcItemPadding.top != 0))
	{
		_stprintf_s(szBuf, _T("%d,%d,%d,%d"), rcItemPadding.left, rcItemPadding.top, rcItemPadding.right, rcItemPadding.bottom);
		pNode->SetAttribute("itemtextpadding", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->nFont != -1)
	{
		DWORD dwFont = pListInfo->nFont;
		_stprintf_s(szBuf, _T("%d"), dwFont);
		pNode->SetAttribute("itemfont", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwTextColor != 0)
	{
		DWORD dwColor = pListInfo->dwTextColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemtextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwBkColor != 0)
	{
		DWORD dwColor = pListInfo->dwBkColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itembkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwSelectedTextColor != 0)
	{
		DWORD dwColor = pListInfo->dwSelectedTextColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemselectedtextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwSelectedBkColor != 0)
	{
		DWORD dwColor = pListInfo->dwSelectedBkColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemselectedbkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwHotTextColor != 0)
	{
		DWORD dwColor = pListInfo->dwHotTextColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemhottextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwHotBkColor != 0)
	{
		DWORD dwColor = pListInfo->dwHotBkColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemhotbkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwDisabledTextColor != 0)
	{
		DWORD dwColor = pListInfo->dwDisabledTextColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemdisabledtextcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwDisabledBkColor != 0)
	{

		DWORD dwColor = pListInfo->dwDisabledBkColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemdisabledbkcolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->dwLineColor != 0)
	{
		DWORD dwColor = pListInfo->dwLineColor;
		_stprintf_s(szBuf, _T("#%02X%02X%02X%02X"), HIBYTE(HIWORD(dwColor)), static_cast<BYTE>(GetBValue(dwColor)), static_cast<BYTE>(GetGValue(dwColor)), static_cast<BYTE>(GetRValue(dwColor)));
		pNode->SetAttribute("itemlinecolor", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListInfo->sBkImage && _tcslen(pListInfo->sBkImage) > 0)
		pNode->SetAttribute("itembkimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListInfo->sBkImage)));

	if (pListInfo->sSelectedImage && _tcslen(pListInfo->sSelectedImage) > 0)
		pNode->SetAttribute("itemselectedimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListInfo->sSelectedImage)));

	if (pListInfo->sHotImage && _tcslen(pListInfo->sHotImage) > 0)
		pNode->SetAttribute("itemhotimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListInfo->sHotImage)));

	if (pListInfo->sDisabledImage && _tcslen(pListInfo->sDisabledImage) > 0)
		pNode->SetAttribute("itemdisabledimage", StringConvertor::WideToUtf8(ConvertImageFileName(pListInfo->sDisabledImage)));

	CDuiString tstrAlgin;
	UINT uTextStyle = pListInfo->uTextStyle;

	if (uTextStyle == DT_LEFT)
		tstrAlgin = _T("left");
	else if (uTextStyle & DT_RIGHT)
		tstrAlgin = _T("right");
	else
		tstrAlgin = _T("center");

	if (tstrAlgin.CompareNoCase(_T("center")) != 0)
		pNode->SetAttribute("itemalign", StringConvertor::WideToUtf8(tstrAlgin));
}

void CLayoutManager::SaveTabLayoutProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	TCHAR szBuf[MAX_PATH] = { 0 };

	SaveContainerProperty(pControl, pNode);

	ASSERT(pControl);
	CTabLayoutUI* pTabLayout = static_cast<CTabLayoutUI*>(pControl->GetInterface(_T("TabLayout")));
	ASSERT(pTabLayout);

	if (pTabLayout->GetCurSel() != 0)
	{
		ZeroMemory(szBuf, sizeof(szBuf));
		_stprintf_s(szBuf, _T("%d"), pTabLayout->GetCurSel());
		pNode->SetAttribute("selectedid", StringConvertor::WideToUtf8(szBuf));
	}
}

void CLayoutManager::SaveChildWindowProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);

	ASSERT(pControl);
	CChildLayoutUI* pChildWindow = static_cast<CChildLayoutUI*>(pControl->GetInterface(_T("ChildLayout")));
	ASSERT(pChildWindow);

	if (!pChildWindow->GetChildLayoutXML().IsEmpty())
	{
		pNode->SetAttribute("xmlfile", StringConvertor::WideToUtf8(pChildWindow->GetChildLayoutXML()));
	}
}

void CLayoutManager::SaveListHeaderProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveContainerProperty(pControl, pNode);

	TCHAR szBuf[MAX_PATH] = { 0 };
	CListHeaderUI * pListHeaderUI = static_cast<CListHeaderUI*>(pControl->GetInterface(_T("ListHeader")));

	if (0 != pListHeaderUI->GetSepWidth())
	{
		_stprintf_s(szBuf, _T("%d"), pListHeaderUI->GetSepWidth());
		pNode->SetAttribute("sepwidth", StringConvertor::WideToUtf8(szBuf));
	}

	if (pListHeaderUI->IsSepImmMode())
	{
		pNode->SetAttribute("sepimm", "true");
	}
}

void CLayoutManager::SaveWebBrowserProperty(CControlUI* pControl, TiXmlElement* pNode)
{
	SaveControlProperty(pControl, pNode);

	CWebBrowserUI * pWebBrowserUI = static_cast<CWebBrowserUI*>(pControl->GetInterface(_T("WebBrowser")));

	if (pWebBrowserUI->IsAutoNavigation())
	{
		pNode->SetAttribute("autonavi", "true");
	}

	if (pWebBrowserUI->GetHomePage() && _tcslen(pWebBrowserUI->GetHomePage()) > 0)
	{
		pNode->SetAttribute("homepage", StringConvertor::WideToUtf8(pWebBrowserUI->GetHomePage()));
	}
}

CString CLayoutManager::m_strSkinDir = _T("");
