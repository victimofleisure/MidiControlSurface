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

// MidiControlSurface.h : main header file for the MidiControlSurface application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include "MidiDevices.h"
#include "MidiWrap.h"

// CMidiControlSurfaceApp:
// See MidiControlSurface.cpp for the implementation of this class
//

class CMainFrame;

class CMidiControlSurfaceApp : public CWinAppEx
{
public:
	CMidiControlSurfaceApp();

	CMainFrame* GetMainFrame();
	bool	OpenMidiOutputDevice(int iDev);

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	CMidiDevices	m_midiDevs;
	CMidiOut	m_midiOut;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMidiControlSurfaceApp theApp;

inline CMainFrame* CMidiControlSurfaceApp::GetMainFrame()
{
	return reinterpret_cast<CMainFrame*>(m_pMainWnd);
}
