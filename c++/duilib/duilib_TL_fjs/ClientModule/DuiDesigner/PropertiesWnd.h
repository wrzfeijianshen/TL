#pragma once
#include "UIlib.h"
#include "UIProperties.h"

//////////////////////////////////////////////////////////////////////////
//CPropertiesWnd

class CPropertiesWnd : public CDockablePane
{
	// 构造
public:
	CPropertiesWnd();
	virtual ~CPropertiesWnd();

	// 实现
public:
	void AdjustLayout();
	void SetVSDotNetLook(BOOL bSet);

	void ShowProperty(CControlUI* pControl);
	void SetPropValue(CControlUI* pControl, int nTag);

protected:
	void SetUIValue(CMFCPropertyGridProperty* pProp, int nTag);

protected:
	CUIProperties m_wndUIProperties;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUIPropChanged(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};