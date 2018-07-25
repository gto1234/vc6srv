// vc6srv.h : main header file for the VC6SRV application
//

#if !defined(AFX_VC6SRV_H__A86B9313_90DF_4DCC_ADA4_3965D6057335__INCLUDED_)
#define AFX_VC6SRV_H__A86B9313_90DF_4DCC_ADA4_3965D6057335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVc6srvApp:
// See vc6srv.cpp for the implementation of this class
//

class CVc6srvApp : public CWinApp
{
public:
	CVc6srvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVc6srvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVc6srvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC6SRV_H__A86B9313_90DF_4DCC_ADA4_3965D6057335__INCLUDED_)
