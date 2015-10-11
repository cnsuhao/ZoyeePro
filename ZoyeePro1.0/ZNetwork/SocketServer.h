#pragma once
#include "znetwork.h"
#include "SocketBase.h"
using namespace ZoyeePro10;

class CSocketServer :	public INetworkModel
{
public:
	virtual CContext* Init(const char* pDesc, int nProtocol = TCP);
	virtual int UnInit();

	virtual int Send(const char* pszbuff, const int nLen, const CContext* pContext);
	virtual CContext* Connect(CContext* pDesc);
	virtual int DisConnect();
	virtual int DisConnect(const CContext* pContext);// kick

private:
	static DWORD WINAPI workThread(void *pParam);
	SOCKET sockCli;
	SOCKET sockSrv;
	CSocketBase initSocket;
};

