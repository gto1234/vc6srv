#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#define N_NETBUFFER_SIZE 1024

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	~CClientSocket();

	void SetMainWindowPointer(void *_ptr);

protected:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void *m_PosToken;
	unsigned char m_sBuffer[N_NETBUFFER_SIZE];

	void SendResponse();
};

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket(void);
	~CServerSocket(void);

	void SetMainWindowPointer(void *_ptr);
	virtual void Close();

	
protected:
	void *m_PosToken;
	CClientSocket m_AcceptSocket;


	virtual void OnAccept(int nErrorCode);
};

#endif