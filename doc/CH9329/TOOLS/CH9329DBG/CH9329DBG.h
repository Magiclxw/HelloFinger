// CH9329DBG.h : main header file for the CH9329DBG application
//

#if !defined(AFX_CH9329DBG_H__F73BB19B_4873_4BCA_B1C2_9ECCC31CD3B8__INCLUDED_)
#define AFX_CH9329DBG_H__F73BB19B_4873_4BCA_B1C2_9ECCC31CD3B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCH9329DBGApp:
// See CH9329DBG.cpp for the implementation of this class
//

class CCH9329DBGApp : public CWinApp
{
public:
	CCH9329DBGApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCH9329DBGApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCH9329DBGApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CH9329DBG_H__F73BB19B_4873_4BCA_B1C2_9ECCC31CD3B8__INCLUDED_)
