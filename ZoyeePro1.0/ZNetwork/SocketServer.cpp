#include "stdafx.h"
#include "SocketServer.h"
#include "SocketBase.h"

CContext* CSocketServer::Init( const char* pDesc, int nProtocol /*= TCP*/ )
{
	CSocketBase::Instance()->CreateConnection(pDesc, true, nProtocol);
	return nullptr;
}

int CSocketServer::UnInit()
{
	return 0;
}

int CSocketServer::Send( const char* pszbuff, const int nLen, CContext* pContext )
{
	return 0;
}

CContext* CSocketServer::Connect( CContext* pDesc )
{
	printNoSurport("CSocketServer::Connect");
	return nullptr;
}

int CSocketServer::DisConnect()
{
	return 0;
}

int CSocketServer::DisConnect( CContext* pContext )
{
	printNoSurport("CSocketServer::DisConnect");
	return 0;
}

DWORD WINAPI CSocketServer::workThread( void *pParam )
{
	CSocketServer* pThis = (CSocketServer*)pParam;

	while (true)
	{

	}

	return 0;
}
