// Dice.h : main header file for the DICE application
//

#if !defined(AFX_DICE_H__4C6E47F2_18D1_4D15_A637_0CD013DF8004__INCLUDED_)
#define AFX_DICE_H__4C6E47F2_18D1_4D15_A637_0CD013DF8004__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDiceApp:
// See Dice.cpp for the implementation of this class
//

class CDiceApp : public CWinApp
{
public:
	CDiceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDiceApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DICE_H__4C6E47F2_18D1_4D15_A637_0CD013DF8004__INCLUDED_)
