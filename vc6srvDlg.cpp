// vc6srvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vc6srv.h"
#include "vc6srvDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CVc6srvDlg dialog

CVc6srvDlg::CVc6srvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVc6srvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVc6srvDlg)
	m_OutBox = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_FirstActivated = true;
}

void CVc6srvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVc6srvDlg)
	DDX_Text(pDX, IDC_EDIT1, m_OutBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVc6srvDlg, CDialog)
	//{{AFX_MSG_MAP(CVc6srvDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_CLEAR, OnFileClear)
	ON_COMMAND(ID_FILE_START, OnFileStart)
	ON_COMMAND(ID_FILE_STOP, OnFileStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVc6srvDlg message handlers

BOOL CVc6srvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	if (m_OutBoxFont.CreatePointFont(100, "Courier New"))
	{
		GetDlgItem(IDC_EDIT1)->SetFont(&m_OutBoxFont);
	}

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVc6srvDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVc6srvDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVc6srvDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	CWnd* pCtrl = GetDlgItem(IDC_EDIT1);

	if (pCtrl == NULL) return;

	pCtrl->MoveWindow(0,0,cx,cy);
}

void CVc6srvDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (m_FirstActivated == true)
	{
		this->StartListening();
		m_FirstActivated = false;
	}
	
}

void CVc6srvDlg::StartListening()
{
	BOOL bOperation;
	
	int nPort = 805;
	CString str;

	m_srvsock.SetMainWindowPointer(this);

	if (m_srvsock.m_hSocket == INVALID_SOCKET)
	{

		bOperation = m_srvsock.Create(nPort);

		if (bOperation)
		{
			str.Format("%d", nPort);
			m_OutBox += "Socket created at port " + str + "\r\n";
			UpdateData(false);

			bOperation = m_srvsock.Listen();
			
			if (bOperation)
			{
				m_OutBox += "Socket listing...\r\n";
				UpdateData(false);
			}
			else
			{
				str.Format("%d", m_srvsock.GetLastError());
				m_OutBox += "Error to listen socket, code = " + str + "\r\n";
				UpdateData(false);
			}

		}
		else
		{
			str.Format("%d", m_srvsock.GetLastError());
			m_OutBox += "Error to create socket, code = " + str + "\r\n";
			UpdateData(false);
		}
	}
	else
	{
		m_OutBox += "Socket already opened...\r\n";
		UpdateData(false);
	}

	
}

void CVc6srvDlg::AddTextToOutBox(CString &str)
{
	this->m_OutBox += str;
	UpdateData(false);
}

void CVc6srvDlg::ShowDump(const unsigned char* pOut, unsigned int nLength)
{
	static const char ASCII[256] =
	{
	 //00  01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
	  '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',    // 0
	  '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',    // 1
	  ' ', '!', '.', '#', '$', '%', '&', '.', '(', ')', '*', '+', '`', '-', '.', '/',    // 2
	  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',    // 3
	  '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',    // 4
	  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',   // 5
	  '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',    // 6
	  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '.',    // 7
	  // In an ASCII Table, this repeats (ASCII is 7 bits)
	  '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',    // 8
	  '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',    // 9
	  ' ', '!', '.', '#', '$', '%', '&', '.', '(', ')', '*', '+', '`', '-', '.', '/',    // A
	  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',    // B
	  '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',    // C
	  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',   // D
	  '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',    // E
	  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '.',    // F
	  };

	if (pOut == NULL) return;

	CString strOut, str;
	strOut += CString("     00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\r\n");
	strOut += CString("     -----------------------------------------------  ----------------\r\n");
	
	int nCurrentLine = 0;
//	int nCurrentColumn = 0;
	int nElapsedSymbols = nLength;

	while(nElapsedSymbols > 0)
	{
		int i;
		int nDecrease;
		//str = "";
		str.Format("%03x| ", nCurrentLine * 16);
		strOut += str;
		if (nElapsedSymbols > 16)
		{
			nDecrease = 16;
		}
		else
		{
			nDecrease = nElapsedSymbols;
		}

		for (i =0; i < nDecrease; i++)
		{
		//	str = "";
			str.Format("%02x ", (unsigned char)(pOut[nCurrentLine * 16 + i]));
			strOut += str;
		}

		if (nDecrease != 16)
		{
			for (i = 0; i < 16 - nDecrease; i++)
			{
				strOut += "   ";
			}
		}

		strOut += " ";

		for (i =0; i < nDecrease; i++)
		{		
			strOut += ASCII[pOut[nCurrentLine * 16 + i]];
		}
		
		if (nDecrease != 16)
		{
			for (i = 0; i < 16 - nDecrease; i++)
			{
				strOut += " ";
			}
		}
		strOut += "\r\n";
		nElapsedSymbols -= nDecrease;


		nCurrentLine++;
	}

	strOut += CString("     -----------------------------------------------  ----------------\r\n");
	m_OutBox += strOut;
	UpdateData(false);
}

void CVc6srvDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	this->SendMessage(WM_CLOSE);
	
}

void CVc6srvDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_srvsock.Close();
	CDialog::OnClose();
}

void CVc6srvDlg::OnFileClear() 
{
	// TODO: Add your command handler code here
	m_OutBox = "";
	UpdateData(false);
	
}

void CVc6srvDlg::OnFileStart() 
{
	// TODO: Add your command handler code here
	this->StartListening();
	
}

void CVc6srvDlg::OnFileStop() 
{
	// TODO: Add your command handler code here
	m_srvsock.Close();
	
}
