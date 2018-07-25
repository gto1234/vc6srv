#include "StdAfx.h"
#include "ServerSocket.h"
#include "vc6srvDlg.h"

CClientSocket::CClientSocket(void)
{
}
CClientSocket::~CClientSocket()
{
}

void CClientSocket::OnClose(int nErrorCode)
{
	CVc6srvDlg *wn = (CVc6srvDlg*)m_PosToken;

	
	this->Close();
	if (wn != NULL)
	{
		//wn->MessageBox("Accepted"); 
		wn->AddTextToOutBox(CString("Closed remotely\r\n"));
	}
	//CAsyncSocket::OnClose( nErrorCode );
}


void CClientSocket::OnReceive(int nErrorCode)
{
	CVc6srvDlg *wn = (CVc6srvDlg*)m_PosToken;
	CString str;

	memset(m_sBuffer, 0, N_NETBUFFER_SIZE);
	int nReadLength = this->Receive( m_sBuffer, N_NETBUFFER_SIZE);

	switch( nReadLength )
	{
		case 0:		
			//Disocnnect
			this->Close();
			wn->AddTextToOutBox(CString("Read 0 bytes. Closed\r\n"));
			break;
		case SOCKET_ERROR:
			str.Format("%d", this->GetLastError());
			wn->AddTextToOutBox(CString("Socket error") + str + "\r\n");			
			break;
		default:
			
			str.Format("%d", nReadLength);
			wn->AddTextToOutBox(CString("Read ") + str + CString(" bytes\r\n"));
			wn->ShowDump(m_sBuffer, nReadLength);

			this->SendResponse();



	}
}


void CClientSocket::SendResponse()
{
	memset(m_sBuffer, 0, N_NETBUFFER_SIZE);
	int nSendLength = 21;
	memcpy(m_sBuffer, "\x00\x13\x01\x01\x32\x02\x09\x4e\x6f\x43\x6f\x6d\x6d\x61\x6e\x64\x04\x03\x3a\xdd\xbb",nSendLength );

	CVc6srvDlg *wn = (CVc6srvDlg*)m_PosToken;
	CString str;
	str.Format("%d", nSendLength);
	wn->AddTextToOutBox(CString("Send ") + str + CString(" bytes\r\n"));
	wn->ShowDump(m_sBuffer, nSendLength);

	this->Send(m_sBuffer, nSendLength);
}

void CClientSocket::SetMainWindowPointer(void *_ptr)
{
	if (_ptr != NULL)
	{
		m_PosToken = _ptr;		
	}
}

CServerSocket::CServerSocket(void)
{
}


CServerSocket::~CServerSocket(void)
{
}


void CServerSocket::OnAccept(int nErrorCode)
{
	CVc6srvDlg *wn = (CVc6srvDlg*)m_PosToken;

	if (this->Accept(m_AcceptSocket))
	{
		CString strIP, str;
		unsigned int nPort;
		m_AcceptSocket.GetPeerName(strIP,nPort);
		str.Format("%d", nPort);

		if (wn != NULL)
		{
			wn->AddTextToOutBox(CString("Incoming connection from ") + strIP + CString(":") + str + CString("\r\n"));
		}
  
	}

	
}

void CServerSocket::SetMainWindowPointer(void *_ptr)
{
	if (_ptr != NULL)
	{
		m_PosToken = _ptr;
		m_AcceptSocket.SetMainWindowPointer(_ptr);
	}
}

void CServerSocket::Close()
{
	CVc6srvDlg *wn = (CVc6srvDlg*)m_PosToken;

	if (m_AcceptSocket.m_hSocket != INVALID_SOCKET)
	{
		if (wn != NULL)
		{
			wn->AddTextToOutBox(CString("Client socket closed\r\n"));
		}
		m_AcceptSocket.Close();
	}


	if (wn != NULL)
	{
		wn->AddTextToOutBox(CString("Listening socket closed\r\n"));
	}
	CAsyncSocket::Close();
}