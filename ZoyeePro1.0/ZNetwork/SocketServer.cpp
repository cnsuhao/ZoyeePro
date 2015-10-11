#include "stdafx.h"
#include "SocketServer.h"

CContext* CSocketServer::Init( const char* pDesc, int nProtocol /*= TCP*/ )
{
	char* pIpPort = new char[strlen(pDesc) + 1];
	strcpy(pIpPort, pDesc);

	char* pIp = strtok(pIpPort, ":");
	int nPort = 0;
	if (pIp)
	{
		nPort = atoi(strtok(NULL, ":"));
	}

	if (nPort <= 0)
	{
		delete pIpPort;
		char pszMsg[1024] = {0};
		sprintf(pszMsg, "CSocketServer::Init.fail--[ip is error][%s]\n", pDesc);
		CContext context;
		context.emAction = ON_ERROR;
		context.pszBuff = pszMsg;
		context.nLen = strlen(pszMsg);
		m_pCallback->OnMSG(&context);
		return nullptr;
	}

	SOCKADDR_IN sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = nPort;
	sock_in.sin_addr.S_un.S_addr = inet_addr(pIp);

	sockSrv = socket(AF_INET, nProtocol == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (bind(sockSrv, (sockaddr*) &sock_in, sizeof(sockaddr)) != 0)
	{
		//error
	}

	listen(sockSrv, 10);

	delete pIpPort;
	return nullptr;
}

int CSocketServer::UnInit()
{
	return 0;
}

int CSocketServer::Send( const char* pszbuff, const int nLen, const CContext* pContext )
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

int CSocketServer::DisConnect( const CContext* pContext )
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
