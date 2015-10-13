#pragma once
#include <string>
#ifndef TCP
#define TCP 10
#endif

using namespace std;

class CSocketBase
{
public:	
	virtual ~CSocketBase(void);
	static CSocketBase* Instance();
	SOCKET CreateConnection(const char* pDesc, bool bIsSrv = true, int nProtocol = TCP);//srv做到bind, cli做到connect
	char* GetAddr(sockaddr_in& sock_in);
private:
	void SetError(const char* pError);
	CSocketBase(void);
	static CSocketBase* ptrSocketbase;
	char* m_pError;
};

