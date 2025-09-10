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

// MidiControlSurfaceView.cpp : implementation of the CMidiControlSurfaceView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MidiControlSurface.h"
#endif

#include "MidiControlSurfaceDoc.h"
#include "MidiControlSurfaceView.h"
#include "ParamsRowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidiControlSurfaceView

IMPLEMENT_DYNCREATE(CMidiControlSurfaceView, CRowView)

// CMidiControlSurfaceView construction/destruction

CMidiControlSurfaceView::CMidiControlSurfaceView()
{
	// TODO: add construction code here

}

CMidiControlSurfaceView::~CMidiControlSurfaceView()
{
}

BOOL CMidiControlSurfaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRowView::PreCreateWindow(cs);
}

CRowDlg	*CMidiControlSurfaceView::CreateRow(int Idx)
{
	CParamsRowDlg	*pRow = new CParamsRowDlg;
	ASSERT(pRow != NULL);
	pRow->SetRowIndex(Idx);
	pRow->Create(IDD_PARAMS_ROW, this);
	return(pRow);
}

void CMidiControlSurfaceView::UpdateRow(int Idx)
{
}

void CMidiControlSurfaceView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	UNREFERENCED_PARAMETER(pSender);
}

// CMidiControlSurfaceView drawing

void CMidiControlSurfaceView::OnDraw(CDC* /*pDC*/)
{
	CMidiControlSurfaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMidiControlSurfaceView diagnostics

#ifdef _DEBUG
void CMidiControlSurfaceView::AssertValid() const
{
	CRowView::AssertValid();
}

void CMidiControlSurfaceView::Dump(CDumpContext& dc) const
{
	CRowView::Dump(dc);
}

CMidiControlSurfaceDoc* CMidiControlSurfaceView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidiControlSurfaceDoc)));
	return (CMidiControlSurfaceDoc*)m_pDocument;
}
#endif //_DEBUG

// CMidiControlSurfaceView message map

BEGIN_MESSAGE_MAP(CMidiControlSurfaceView, CRowView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRowView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRowView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRowView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMidiControlSurfaceView message handlers

const CRowView::COLINFO CMidiControlSurfaceView::m_arrColInfo[] = {
	#define COLUMNDEF(name) {IDC_ROW_##name, IDS_COL_##name},
	#include "ParamsDef.h"
};

int CMidiControlSurfaceView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRowView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// The row view assumes the view's control ID can be mapped to a resource
	// string which it uses as a prefix for reading and writing column widths.
	// The framework necessarily sets the view's ID to AFX_IDW_PANE_FIRST, but
	// that ID maps to an unhelpful string, so we temporarily override the ID.
	int	nPrevID = GetDlgCtrlID();
	SetDlgCtrlID(ID_PARAMS);	// temporarily give view a more convenient ID
	CreateCols(COLUMNS, m_arrColInfo, IDD_PARAMS_ROW);
	SetDlgCtrlID(nPrevID);	// restore view's previous ID
	return 0;
}

void CMidiControlSurfaceView::OnInitialUpdate()
{
	CRowView::OnInitialUpdate();
	CreateRows(1);
}

void CMidiControlSurfaceView::OnDestroy()
{
	int	nPrevID = GetDlgCtrlID();	// temporarily give view a more convenient ID
	SetDlgCtrlID(ID_PARAMS);
	CRowView::OnDestroy();
	SetDlgCtrlID(nPrevID);	// restore view's previous ID
}
