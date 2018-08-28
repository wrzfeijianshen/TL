#pragma once
#include "ViewTree.h"
#include "UIlib.h"
using DuiLib::CControlUI;

//////////////////////////////////////////////////////////////////////////
//CClassViewTree

class CClassViewTree : public CViewTree
{
// 构造
public:
	CClassViewTree();
	virtual ~CClassViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelChanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//////////////////////////////////////////////////////////////////////////
//CClassView

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void AdjustLayout();
	void OnChangeVisualStyle();

public:
	void InsertUITreeItem(CControlUI* pControl,LPCTSTR pstrName=NULL);
	BOOL RemoveUITreeItem(CControlUI* pControl);
	BOOL RemoveUITreeItem(HTREEITEM hItem);
	void SelectUITreeItem(CControlUI* pControl);
	void RenameUITreeItem(CControlUI* pControl, LPCTSTR lpszName);

protected:
	BOOL RemoveTreeItem(CControlUI* pControl);
	BOOL RemoveTreeItem(HTREEITEM hItem);

private:
	CClassViewTree m_wndClassView;
	CImageList m_ClassViewImages;

	HTREEITEM m_hItemCur;	//当前被选中的Item
	HTREEITEM m_hItemPrev;	//上一个被选中的Item

// 重写
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

