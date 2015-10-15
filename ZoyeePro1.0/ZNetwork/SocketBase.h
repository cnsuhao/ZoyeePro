#pragma once
#include <string>
#ifndef TCP
#define TCP 0
#endif

using namespace std;

class CSocketBase
{
public:	
	virtual ~CSocketBase(void);
	static CSocketBase* Instance();
	SOCKET CreateConnection(const char* pDesc, bool bIsSrv = true, int nProtocol = TCP);//srv做到bind, cli做到connect
	static char* GetAddr(sockaddr_in& sock_in);
	static char* GetFullAddr(sockaddr_in& sock_in);
	static int GetPort(sockaddr_in& sock_in);
	static void Close(SOCKET& s);
private:
	void SetError(const char* pError);
	CSocketBase(void);
	static CSocketBase* ptrSocketbase;
	char* m_pError;
};

