#include "stdafx.h"
#include "MidiControlSurface.h"
#include "ParamsRowDlg.h"
#include "Midi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CParamsRowDlg

CParamsRowDlg::CParamsRowDlg() : CRowDlg(IDD_PARAMS_ROW)
{
	m_nPrevEvent = -1;
}

CParamsRowDlg::~CParamsRowDlg()
{
}

void CParamsRowDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_ROW_EVENT_COMBO, m_comboEvent);
	DDX_Control(pDX, IDC_ROW_CHANNEL_COMBO, m_comboChannel);
	DDX_Control(pDX, IDC_ROW_CONTROL_EDIT, m_editControl);
	DDX_Control(pDX, IDC_ROW_CONTROL_SPIN, m_spinControl);
	DDX_Control(pDX, IDC_ROW_VAL_SLIDER, m_sliderVal);
	DDX_Control(pDX, IDC_ROW_VAL_EDIT, m_editVal);
	DDX_Control(pDX, IDC_ROW_VAL_SPIN, m_spinVal);

	CRowDlg::DoDataExchange(pDX);
}

BOOL CParamsRowDlg::OnInitDialog()
{
	CRowDlg::OnInitDialog();

	// initialize child controls
	m_comboEvent.SetCurSel(MIDI_CVM_CONTROL - 1);
	m_comboChannel.SetCurSel(0);
	m_editControl.SetVal(1);
	m_sliderVal.SetRange(0, MIDI_NOTE_MAX);
	m_sliderVal.SetDefaultPos(MIDI_NOTES / 2);
	m_editControl.SetRange(0, MIDI_NOTE_MAX);
	m_sliderVal.SetEditCtrl(&m_editVal);
	m_editVal.SetRange(0, MIDI_NOTE_MAX);

	return TRUE;  // return TRUE unless you set the focus to a control
}

// CParamsRowDlg message map

BEGIN_MESSAGE_MAP(CParamsRowDlg, CRowDlg)
	ON_CBN_SELCHANGE(IDC_ROW_EVENT_COMBO, OnSelChangedEvent)
	ON_NOTIFY(NEN_CHANGED, IDC_ROW_VAL_EDIT, OnChangedVal)
END_MESSAGE_MAP()

void CParamsRowDlg::OnSelChangedEvent()
{
	const int nPBSteps = MIDI_PITCH_BEND_STEPS;
	int	iCmd = m_comboEvent.GetCurSel() + 1;	// combo doesn't include note off
	int	nMin, nMax, nMid;
	double	fVal = m_editVal.GetVal();
	if (iCmd == MIDI_CVM_WHEEL) {
		nMin = -nPBSteps / 2;
		nMax = nPBSteps / 2 - 1;
		nMid = 0;
		if (m_nPrevEvent != MIDI_CVM_WHEEL) {
			fVal = Round(fVal / MIDI_NOTES * nPBSteps - nPBSteps / 2);
		}
	} else {
		nMin = 0;
		nMax = MIDI_NOTE_MAX;
		nMid = MIDI_NOTES / 2;
		if (m_nPrevEvent == MIDI_CVM_WHEEL) {
			fVal = Round((fVal + nPBSteps / 2) / nPBSteps * MIDI_NOTES);
		}
	}
	m_nPrevEvent = iCmd;
	fVal = CLAMP(fVal, nMin, nMax);
	m_sliderVal.SetRange(nMin, nMax);
	m_editVal.SetRange(nMin, nMax);
	m_sliderVal.SetDefaultPos(nMid);
	m_editVal.SetVal(fVal);
}

void CParamsRowDlg::OnChangedVal(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMainFrame*	pFrame = theApp.GetMainFrame();
	ASSERT(pFrame != NULL);
	if (theApp.m_midiOut.IsOpen()) {
		int	iCmd = m_comboEvent.GetCurSel() + 1;	// combo doesn't include note off
		int	nControl = m_editControl.GetIntVal();
		int	nVal = m_editVal.GetIntVal();
		int	nP1, nP2;
		switch (iCmd) {
		case MIDI_CVM_NOTE_ON:
		case MIDI_CVM_KEY_AFT:
		case MIDI_CVM_CONTROL:
			nP1 = nControl;
			nP2 = nVal;
			break;
		case MIDI_CVM_PATCH:
		case MIDI_CVM_CHAN_AFT:
			nP1 = nVal;
			nP2 = 0;
			break;
		case MIDI_CVM_WHEEL:
			{
				nVal = nVal + MIDI_PITCH_BEND_STEPS / 2;
				nP1 = nVal & 0x7f;
				nP2 = nVal >> 7;
			}
			break;
		}
		int	nCmdStat = MIDI_IDX_CMD(iCmd);
		int	iChan = m_comboChannel.GetCurSel();
		DWORD	nMsg = MakeMidiMsg(nCmdStat, iChan, nP1, nP2);
		theApp.m_midiOut.OutShortMsg(nMsg);
	}
	*pResult = 0;
}
