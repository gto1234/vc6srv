// vc6srvDlg.h : header file
//

#if !defined(AFX_VC6SRVDLG_H__F6D3FB51_6743_44E7_A957_30C8867CF584__INCLUDED_)
#define AFX_VC6SRVDLG_H__F6D3FB51_6743_44E7_A957_30C8867CF584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "ServerSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CVc6srvDlg dialog

class CVc6srvDlg : public CDialog
{
// Construction
public:
	CVc6srvDlg(CWnd* pParent = NULL);	// standard constructor
	void AddTextToOutBox(CString &str);
	void ShowDump(const unsigned char* pOut, unsigned int nLength);

// Dialog Data
	//{{AFX_DATA(CVc6srvDlg)
	enum { IDD = IDD_VC6SRV_DIALOG };
	CString	m_OutBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVc6srvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	bool m_FirstActivated;
	void StartListening();
	CServerSocket m_srvsock;
	CFont m_OutBoxFont;
	

	// Generated message map functions
	//{{AFX_MSG(CVc6srvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnFileExit();
	afx_msg void OnClose();
	afx_msg void OnFileClear();
	afx_msg void OnFileStart();
	afx_msg void OnFileStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC6SRVDLG_H__F6D3FB51_6743_44E7_A957_30C8867CF584__INCLUDED_)
