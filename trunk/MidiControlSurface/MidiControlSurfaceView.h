// Copyleft 2025 Chris Korda
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.
/*
        chris korda
 
		revision history:
		rev		date	comments
        00      03mar25	initial version

*/

// MidiControlSurfaceView.h : interface of the CMidiControlSurfaceView class
//

#pragma once

#include "RowView.h"

class CMidiControlSurfaceView : public CRowView
{
protected: // create from serialization only
	CMidiControlSurfaceView();
	DECLARE_DYNCREATE(CMidiControlSurfaceView)

// Attributes
public:
	CMidiControlSurfaceDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual CRowDlg	*CreateRow(int Idx);
	virtual void UpdateRow(int Idx);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Implementation
public:
	virtual ~CMidiControlSurfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	enum {
		#define COLUMNDEF(name) COL_##name,
		#include "ParamsDef.h"
		COLUMNS
	};
	static const CRowView::COLINFO m_arrColInfo[];

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in MidiControlSurfaceView.cpp
inline CMidiControlSurfaceDoc* CMidiControlSurfaceView::GetDocument() const
   { return reinterpret_cast<CMidiControlSurfaceDoc*>(m_pDocument); }
#endif

