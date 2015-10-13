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

int CIocpServer::Send( const char* pszbuff, const int nLen, CContext* pContext )
{
	return 0;
}

CContext* CIocpServer::Connect( CContext* pDesc )
{
	printNoSurport("CIocpServer::Connect");
	return nullptr;
}

int CIocpServer::DisConnect()
{
	printNoSurport("CIocpServer::DisConnect(void)");
	return 0;
}

int CIocpServer::DisConnect( CContext* pContext )
{
	CContext context;
	
	if (pContext == nullptr || pContext->pHandle == nullptr)
	{
		context.emAction = ON_ERROR;
		context.pszBuff = "[CIocpServer::DisConnect].context is nullptr or Handle is null\n";
		context.nLen = strlen("[CIocpServer::DisConnect].context is nullptr or Handle is null\n");
		m_pCallback->OnMSG(&context);
		return -1;
	}

	context.emAction = ON_SYSTEM;
	context.pszDesc = pContext->pszDesc;
	context.pszBuff = new char[1024];
	sprintf(context.pszBuff, "[CIocpServer::DisConnect].kick the socket[%][%s]\n", (int)context.pHandle, context.pszDesc);
	context.nLen = strlen(context.pszBuff);
	m_pCallback->OnMSG(&context);
	delete context.pszBuff;
	closesocket((SOCKET)pContext->pHandle);
	return 0;
}
