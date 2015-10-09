#include "stdafx.h"
#include "IocpServer.h"

CContext* CIocpServer::Init( const char* pDesc, int nProtocol /*= TCP*/ )
{
	return nullptr;
}

int CIocpServer::UnInit()
{
	return 0;
}

int CIocpServer::Send( const char* pszbuff, const int nLen, const CContext* pContext )
{
	return 0;
}

CContext* CIocpServer::Connect( CContext* pDesc )
{
	return nullptr;
}

int CIocpServer::DisConnect()
{
	return 0;
}

int CIocpServer::DisConnect( const CContext* pContext )
{
	return 0;
}
