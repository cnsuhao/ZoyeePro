#include "stdafx.h"
#include "SocketBase.h"


CSocketBase::CSocketBase(void)
{
	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		printf("wsaStartup fail!\n");
	}
	else
	{
		printf("wsaStartup suss!\n");
	}
}


CSocketBase::~CSocketBase(void)
{
	WSACleanup();
}
