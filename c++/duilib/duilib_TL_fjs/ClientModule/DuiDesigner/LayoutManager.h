#pragma once
#include "UIlib.h"

using DuiLib::CContainerUI;
using DuiLib::CPaintManagerUI;
using DuiLib::CWindowWnd;
using DuiLib::TNotifyUI;
using DuiLib::IDialogBuilderCallback;
using DuiLib::WindowImplBase;
using DuiLib::UILIB_RESOURCETYPE;
using DuiLib::CDuiString;

#define EXPORT_UI_SCRIPT

#if defined(EXPORT_UI_SCRIPT)
#include "tinyxml.h"
#endif

//////////////////////////////////////////////////////////////////////////
//CFormUI 主界面结构控件(包含root)

class CFormUI : public CContainerUI
{
public:
	CFormUI();
	virtual ~CFormUI();

public:

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetPos(RECT rc);
	void SetFileRoot(CControlUI* pFileRoot);
	CControlUI* GetFileRoot();
public:

	//Size
	SIZE GetInitSize();
	void SetInitSize(int cx, int cy);

	//Caption
	RECT& GetCaptionRect();
	void SetCaptionRect(RECT& rcCaption);

	//SizeBox
	RECT& GetSizeBox();
	void SetSizeBox(RECT& rcSizeBox);

	//RoundCorner
	SIZE GetRoundCorner() const;
	void SetRoundCorner(int cx, int cy);

	//MaxInfo
	SIZE GetMinInfo() const;
	SIZE GetMaxInfo() const;

	//MinInfo
	void SetMinInfo(int cx, int cy);
	void SetMaxInfo(int cx, int cy);

	//ShowDirty
	bool IsShowUpdateRect() const;
	void SetShowUpdateRect(bool bShow);

	//Alpha
	void SetAlpha(int iOpacity);
	int GetAlpha() const;

	//BkTrans
	void SetBackgroundTransparent(bool bTrans);
	bool GetBackgroundTransparent() const;

	//DefaultFontColor
	void SetDefaultFontColor(DWORD dwColor);
	DWORD GetDefaultFontColor() const;

	//SelectedFontColor
	void SetDefaultSelectedFontColor(DWORD dwColor);
	DWORD GetDefaultSelectedFontColor() const;

	//DisabledFontColor
	void SetDefaultDisabledFontColor(DWORD dwColor);
	DWORD GetDefaultDisabledFontColor() const;

	//LinkFontColor
	void SetDefaultLinkFontColor(DWORD dwColor);
	DWORD GetDefaultLinkFontColor() const;

	//LinkHoverFontColor
	void SetDefaultLinkHoverFontColor(DWORD dwColor);
	DWORD GetDefaultLinkHoverFontColor() const;

private:
	CControlUI*	m_pFileRoot;		//xml文件中的根节点控件
};

//////////////////////////////////////////////////////////////////////////
//CFormTestWnd

class CFormTestWnd : public WindowImplBase, public INotifyUI
{

public:
	static CFormTestWnd* getInstance(CDuiString strXmlFile);
	~CFormTestWnd();
	
	void CreateFrame();
	void InitData(TNotifyUI& msg);

public:

	//@override function
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND hWnd);
	LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	void InitWindow();
	CControlUI* CreateControl(LPCTSTR pstrClassName);
	void Notify(TNotifyUI& msg);

protected:

	CDuiString GetSkinFolder();
	CDuiString GetSkinFile();
	LPCTSTR GetWindowClassName() const;
	UILIB_RESOURCETYPE GetResourceType() const;

private:
	static CFormTestWnd* g_instance;
	CFormTestWnd(CDuiString strXmlFile);

	CDuiString m_strXmlFile;
};

//////////////////////////////////////////////////////////////////////////
//CLayoutManager

class CLayoutManager : public IDialogBuilderCallback
{
public:
	CLayoutManager(void);
	virtual ~CLayoutManager(void);

public:
	void Init(HWND hWnd,LPCTSTR pstrLoad);
	void Reload(LPCTSTR pstrLoad);

	void Draw(CDC* pDC);
	void DrawAuxBorder(CDC* pDC,CControlUI* pControl);
	void DrawGrid(CDC* pDC,CRect& rect);

	static CControlUI* NewUI(int nClass,CRect& rect,CControlUI* pParent, CLayoutManager* pLayout);
	static BOOL DeleteUI(CControlUI* pControl);
	static void ReleaseExtendedAttrib(CControlUI* pControl, CPaintManagerUI* pManager);
	CPaintManagerUI* GetManager();
	inline CFormUI* GetForm() const;
	CControlUI* FindControl(::CPoint point) const;

	void TestForm(LPCTSTR pstrFile);		//测试窗体 (ctrl + T)
	BOOL IsEmptyForm() const;
	void AlignLeft(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignRight(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignTop(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignBottom(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignCenterVertically(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignCenterHorizontally(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignHorizontal(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignVertical(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignSameWidth(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignSameHeight(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void AlignSameSize(CControlUI* pFocused,CArray<CControlUI*,CControlUI*>& arrSelected);
	void ShowGrid(bool bShow);
	bool IsShowGrid() const;
	void ShowAuxBorder(bool bShow);
	bool IsShowAuxBorder() const;
	void MicoMoveUp(CArray<CControlUI*,CControlUI*>& arrSelected,int nMoved);
	void MicoMoveDown(CArray<CControlUI*,CControlUI*>& arrSelected,int nMoved);
	void MicoMoveLeft(CArray<CControlUI*,CControlUI*>& arrSelected,int nMoved);
	void MicoMoveRight(CArray<CControlUI*,CControlUI*>& arrSelected,int nMoved);

	bool SaveSkinFile(LPCTSTR pstrPathName);
	static void SaveProperties(CControlUI* pControl, TiXmlElement* pParentNode
		, BOOL bSaveChildren = TRUE);

	void SetDefaultUIName(CControlUI* pControl);

	LPCTSTR GetSkinDir() const { return m_strSkinDir; }

	static CControlUI* CloneControls(CControlUI* pControl);
	static CControlUI* CloneControl(CControlUI* pControl);

	CControlUI* CreateControl(LPCTSTR pstrClass);

	/*	获取余下文件路径
	*@breif 如果设置了资源路径,则返回余下文件路径(文件路径 = 资源路径 + 余下的文件路径)
	*@param sTempPath		临时保存输出路径(避免函数执行完毕，局部对象被回收)
	*@param lpOutFileName	文件输出路径(传入时为完整原路径, 传出时为余下文件路径)
	*@param bShowBox		是否弹出失败的MessageBox提示
	*/
	static BOOL ConvertSurplusFileName(DuiLib::CDuiString& sTempPath, LPCTSTR& lpOutFileName, BOOL bShowBox = TRUE);


	// 显示路径对话框
	CDuiString ShowBrowseDlg(HWND hWnd, LPCTSTR lpStr);

	// 浏览路径对话框回调函数
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData);

protected:
	static void SaveControlProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveLabelProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveButtonProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveOptionProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveProgressProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveSliderProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveEditProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveRichEditProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveScrollBarProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveListProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveComboProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveListHeaderProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveListHeaderItemProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveListElementProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveContainerProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveHorizontalLayoutProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveTileLayoutProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveActiveXProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveListContainerElementProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveItemProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveTabLayoutProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveChildWindowProperty(CControlUI* pControl, TiXmlElement* pNode);
	static void SaveWebBrowserProperty(CControlUI* pControl, TiXmlElement* pNode);

	static CString ConvertImageFileName(LPCTSTR pstrImageAttrib);

protected:

	void __LoadXmlUI(LPCTSTR pstrLoad, bool bAttachDialog = true);

	class CDelayRepos
	{
	public:
		CDelayRepos();
		~CDelayRepos();

	public:
		BOOL AddParent(CControlUI* pControl);
		void Repos();

	private:
		CArray<CControlUI*,CControlUI*> m_arrDelay;
	};

private:
	CPaintManagerUI m_Manager;
	CFormUI* m_pFormUI;
	static CString m_strSkinDir;

	bool m_bShowGrid;				//是否显示网格
	bool m_bShowAuxBorder;			//是否显示外围边框
};