#include "stdafx.h"
#include "SocketBase.h"


CSocketBase::CSocketBase(void)
{
	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		SetError("socket初始化失败了");
	}	
}


CSocketBase::~CSocketBase(void)
{
	WSACleanup();
}

CSocketBase* CSocketBase::Instance()
{
	if (ptrSocketbase == nullptr)
	{
		ptrSocketbase = new CSocketBase;
	}
	return ptrSocketbase;
}

SOCKET CSocketBase::CreateConnection( const char* pDesc, bool bIsSrv /*= true*/, int nProtocol /*= TCP*/ )
{
	char pszDesc[32] = {0};
	strcpy(pszDesc, pDesc);
	char *pIp = NULL, *pPort = NULL;
	int nPort;
	pIp = strtok(pszDesc, ":");
	if (pIp)
	{
		nPort = atoi(strtok(NULL, ":"));
		if (nPort <= 0 && nPort >= 0xffff)
		{
			SetError("IP地址还有端口解析有错啦!");
			return INVALID_SOCKET;
		}
	}
	else
	{
		SetError("IP地址还有端口解析有错啦!");
		return INVALID_SOCKET;
	}
	
	SOCKET _socket = socket(AF_INET, (nProtocol == TCP) ? SOCK_STREAM : SOCK_DGRAM, 0);
	SOCKADDR_IN sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(nPort);
	sock_in.sin_addr.S_un.S_addr = inet_addr(pIp);
	if (bIsSrv)
	{
		if(bind(_socket, (const sockaddr*) &sock_in, sizeof(sock_in)) != 0)
		{
			SetError("端口绑不上去, 查查看有没有被占用!");
			return INVALID_SOCKET;
		}

		listen(_socket, 10);
		return _socket;
	}
	else
	{
		if(connect(_socket, (const sockaddr*) &sock_in, sizeof(sock_in)) != 0)
		{
			SetError("连上不服务啦!");
			return INVALID_SOCKET;
		}
	}
	SetError("一般不会出现的错误!");
	return INVALID_SOCKET;
}

void CSocketBase::SetError( const char* pError )
{
	m_pError = (char*)pError;
	printf("\n[有错误出现] ==> ");
	printf(pError);
}

char* CSocketBase::GetAddr( sockaddr_in& sock_in )
{
	return inet_ntoa(sock_in.sin_addr);
}

char* CSocketBase::GetFullAddr( sockaddr_in& sock_in )
{
	static char szFullIP[64] = {0};
	sprintf(szFullIP, "%s:%d", inet_ntoa(sock_in.sin_addr), htons(sock_in.sin_port));
	return szFullIP;
}

int CSocketBase::GetPort( sockaddr_in& sock_in )
{
	return htons(sock_in.sin_port);
}

CSocketBase* CSocketBase::ptrSocketbase = nullptr;
