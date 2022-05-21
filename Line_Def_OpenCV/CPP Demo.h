// CPP Demo.h : main header file for the CPP DEMO application
//

#if !defined(AFX_CPPDEMO_H__CCB8F2D7_5F7C_4E46_91BB_4C5E20B4FB74__INCLUDED_)
#define AFX_CPPDEMO_H__CCB8F2D7_5F7C_4E46_91BB_4C5E20B4FB74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCPPDemoApp:
// See CPP Demo.cpp for the implementation of this class
//



class CCPPDemoApp : public CWinApp
{
public:
	CCPPDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCPPDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCPPDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPDEMO_H__CCB8F2D7_5F7C_4E46_91BB_4C5E20B4FB74__INCLUDED_)
