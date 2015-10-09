#pragma once
#include "znetwork.h"
using namespace ZoyeePro10;

class CIocpServer : public INetworkModel
{
public:
	virtual CContext* Init(const char* pDesc, int nProtocol = TCP);
	virtual int UnInit();

	virtual int Send(const char* pszbuff, const int nLen, const CContext* pContext);
	virtual CContext* Connect(CContext* pDesc);
	virtual int DisConnect();
	virtual int DisConnect(const CContext* pContext);// kick
};

