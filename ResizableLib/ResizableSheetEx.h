#if !defined(AFX_RESIZABLESHEETEX_H__INCLUDED_)
#define AFX_RESIZABLESHEETEX_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2002 by Paolo Messina
// (http://www.geocities.com/ppescher - ppescher@yahoo.com)
//
// The contents of this file are subject to the Artistic License (the "License").
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.opensource.org/licenses/artistic-license.html
//
// If you find this code useful, credits would be nice!
//
/////////////////////////////////////////////////////////////////////////////

#include "ResizableLayout.h"
#include "ResizableGrip.h"
#include "ResizableMinMax.h"
#include "ResizableState.h"

/////////////////////////////////////////////////////////////////////////////
// ResizableSheetEx.h : header file
//

class CResizableSheetEx : public CPropertySheetEx, public CResizableLayout,
						public CResizableGrip, public CResizableMinMax,
						public CResizableState
{
	DECLARE_DYNAMIC(CResizableSheetEx)

// Construction
public:
	CResizableSheetEx();
	CResizableSheetEx(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0,
		HBITMAP hbmWatermark = NULL, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
	CResizableSheetEx(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0,
		HBITMAP hbmWatermark = NULL, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);

// Attributes
private:
	// support for temporarily hiding the grip
	DWORD m_dwGripTempState;

	// flags
	BOOL m_bEnableSaveRestore;
	BOOL m_bRectOnly;
	BOOL m_bSavePage;

	// layout vars
	CSize m_sizePageTL, m_sizePageBR;

	// internal status
	CString m_sSection;			// section name (identifies a parent window)

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizableSheetEx)
	public:
	virtual BOOL OnInitDialog();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void RefreshLayout();
	virtual ~CResizableSheetEx();

// used internally
private:
	void PresetLayout();
	void PrivateConstruct();
	void SavePage();
	void LoadPage();

	BOOL IsWizard() const { return (m_psh.dwFlags & PSH_WIZARD); }
	BOOL IsWizard97() const { return (m_psh.dwFlags & PSH_WIZARD97); }

// callable from derived classes
protected:
	// section to use in app's profile
	void EnableSaveRestore(LPCTSTR pszSection, BOOL bRectOnly = FALSE,
		BOOL bWithPage = FALSE);
	int GetMinWidth();	// minimum width to display all buttons


	virtual CWnd* GetResizableWnd() const
	{
		// make the layout know its parent window
		return CWnd::FromHandle(m_hWnd);
	};

// Generated message map functions
protected:
	virtual BOOL CalcSizeExtra(HWND hWndChild, CSize sizeChild, CSize& sizeExtra);
	virtual BOOL ArrangeLayoutCallback(LayoutInfo& layout) const;
	//{{AFX_MSG(CResizableSheetEx)
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg BOOL OnPageChanging(NMHDR* pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// AFX_RESIZABLESHEETEX_H__INCLUDED_
