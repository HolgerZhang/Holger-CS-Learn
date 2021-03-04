// CatAndMouse.h : main header file for the CATANDMOUSE application
//

#if !defined(AFX_CATANDMOUSE_H__A32BC945_06FC_11D7_A056_00065BD708D9__INCLUDED_)
#define AFX_CATANDMOUSE_H__A32BC945_06FC_11D7_A056_00065BD708D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCatAndMouseApp:
// See CatAndMouse.cpp for the implementation of this class
//

class CCatAndMouseApp : public CWinApp
{
public:
	CCatAndMouseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatAndMouseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCatAndMouseApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATANDMOUSE_H__A32BC945_06FC_11D7_A056_00065BD708D9__INCLUDED_)
