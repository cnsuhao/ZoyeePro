#pragma once
#include "ZNetwork.h"

using namespace ZoyeePro10;
class CSocketBase;
class CSocketServer :	public INetworkModel
{
public:
	CSocketServer();
	virtual CContext* Init(const char* pDesc, int nProtocol = TCP);
	virtual int UnInit();

	virtual int Send(const char* pszbuff, const int nLen, CContext* pContext);
	virtual CContext* Connect(CContext* pDesc);
	virtual int DisConnect();
	virtual int DisConnect(CContext* pContext);// kick

private:
	static DWORD WINAPI workThread(void *pParam);
	SOCKET sockCli;
	SOCKET sockSrv;
	bool bIsInit;
	CContext* m_pContext;
};

