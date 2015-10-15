#pragma once
#include "znetwork.h"
#include "LockerHelper.h"
using namespace ZoyeePro10;

class CSocketBase;

class CSocketClient : public INetworkModel
{
public:
	CSocketClient(void);
	virtual ~CSocketClient(void);

	virtual CContext* Init(const char* pDesc, int nProtocol = TCP);
	virtual int UnInit();

	virtual int Send(const char* pszbuff, const int nLen, CContext* pContext);
	virtual CContext* Connect(CContext* pDesc);
	virtual int DisConnect();
	virtual int DisConnect(CContext* pContext);// 不必实现
	char szDesc[32];
	
private:
	static DWORD WINAPI workThread(void* lpParam);
	GetSetFunc(bool , IsConnectd, m_bIsConnect);

	bool m_bIsInit;
	int m_nProtocol;

	CSocketBase* m_pSocketBase;
	CContext* m_pContext;
	SOCKET m_sockCli;	
	CKey key;
};

