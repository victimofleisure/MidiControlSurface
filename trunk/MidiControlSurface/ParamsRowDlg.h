#pragma once

#include "RowDlg.h"
#include "EditSliderCtrl.h"
#include "NumEdit.h"
#include "NumSpin.h"
#include "MainFrm.h"

class CWhorldDoc;

class CParamsRowDlg : public CRowDlg
{
// Construction
public:
	CParamsRowDlg();

// Operations

// Implementation
public:
	virtual ~CParamsRowDlg();

protected:
// Types

// Data members
	CComboBox	m_comboEvent;
	CComboBox	m_comboChannel;
	CNumEdit	m_editControl;
	CNumSpin	m_spinControl;
	CEditSliderCtrl	m_sliderVal;
	CNumEdit	m_editVal;
	CNumSpin	m_spinVal;
	int		m_nPrevEvent;

// Overrides
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

// Helpers

// Generated message map functions
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSelChangedEvent();
	afx_msg void OnChangedVal(NMHDR* pNMHDR, LRESULT* pResult);
};
