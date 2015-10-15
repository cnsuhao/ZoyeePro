#include "stdafx.h"
#include "SocketServer.h"
#include "SocketBase.h"

#define MAXBUFFSIZE 1024

CContext* CSocketServer::Init( const char* pDesc, int nProtocol /*= TCP*/ )
{
	if (bIsInit)
	{
		m_pContext->pszBuff = "已经初始化过, 无法再次初始化";
		m_pContext->CalcBuffStrLen();
		m_pCallback->OnMSG(m_pContext);
		return m_pContext;
	}
	sockSrv = sockCli = INVALID_SOCKET;
	CContext* pContext = new CContext;
	pContext->_s = CSocketBase::Instance()->CreateConnection(pDesc, true, nProtocol);
	if (pContext->_s != INVALID_SOCKET)
	{
		pContext->emAction = ON_SYSTEM;
		pContext->pszBuff = "端口已经监听!";
		pContext->CalcBuffStrLen();
		sockSrv = pContext->_s;
		m_pCallback->OnMSG(pContext);
		m_pContext = pContext;

		m_phThread = new HANDLE[1];
		m_nThreadSize = 1;
		m_phThread[0] = CreateThread(0, 0, workThread, this, 0, 0);
		return pContext;
	}
	return nullptr;
}

int CSocketServer::UnInit()
{
	if (bIsInit)
	{
		return 0;
	}

	if (sockCli != INVALID_SOCKET)
	{
		CSocketBase::Close(sockCli);		
	}
	if (sockSrv != INVALID_SOCKET)
	{
		CSocketBase::Close(sockSrv);
	}
	
	if (m_phThread[0] != 0)
	{
		TerminateThread(m_phThread[0], 0);
	}
	bIsInit = false;
	return 0;
}

int CSocketServer::Send( const char* pszbuff, const int nLen, CContext* pContext )
{
	if (pContext->_c != INVALID_SOCKET)
	{
		return send(pContext->_c, pszbuff, nLen, 0);
	}
	return -1;
}

CContext* CSocketServer::Connect( CContext* pDesc )
{
	printNoSurport("CSocketServer::Connect");
	return nullptr;
}

int CSocketServer::DisConnect()
{
	printNoSurport("CSocketServer::DisConnect");
	return 0;
}

int CSocketServer::DisConnect( CContext* pContext )
{
	CSocketBase::Close(pContext->_c);
	static char szBuff[128] = {0};
	sprintf(&szBuff[0], "已断开[%d][%s]", pContext->_c, pContext->pszDesc);
	pContext->pszBuff = szBuff;
	pContext->CalcBuffStrLen();
	m_pCallback->OnMSG(pContext);
	pContext->pszBuff = NULL;//防止静态变量释放可能出错
	pContext->Release();
	return 0;
}

DWORD WINAPI CSocketServer::workThread( void *pParam )
{
	CSocketServer* pThis = (CSocketServer*)pParam;
	SOCKADDR_IN remoteSockaddr;

	int nSize = sizeof(remoteSockaddr);
	int nLen = 0;
	char szBuff[MAXBUFFSIZE] = {0};
	while (true)
	{
		pThis->sockCli = accept(pThis->sockSrv, (sockaddr*)&remoteSockaddr,  &nSize);
		if (pThis->sockCli == INVALID_SOCKET)
		{
			DWORD dw = GetLastError();
			pThis->m_pContext->pszBuff = "Accept处出了问题";
			pThis->m_pContext->CalcBuffStrLen();
			pThis->m_pCallback->OnMSG(pThis->m_pContext);
			Sleep(10);
			continue;
		}		

		pThis->m_pContext->pszDesc = CSocketBase::GetFullAddr(remoteSockaddr);
		pThis->m_pContext->_c = pThis->sockCli;
		pThis->m_pContext->_s = pThis->sockSrv;
		sprintf(szBuff, "Accept进来一个连接[%d], addr[%s]", pThis->sockCli, pThis->m_pContext->pszDesc);
		pThis->m_pContext->pszBuff = szBuff;
		pThis->m_pCallback->OnMSG(pThis->m_pContext);

		while (true)
		{
			nLen = recv(pThis->sockCli, szBuff, MAXBUFFSIZE - 1, 0);
			if (nLen <= 0)
			{
				pThis->m_pContext->pszBuff = "Recv异常, 关闭这个Socket";
				pThis->m_pContext->CalcBuffStrLen();
				pThis->m_pCallback->OnMSG(pThis->m_pContext);
				CSocketBase::Close(pThis->sockCli);
				break;
			}
			szBuff[nLen] = 0;
			pThis->m_pContext->pszBuff = szBuff;
			pThis->m_pContext->nLen = nLen;
			pThis->m_pCallback->OnMSG(pThis->m_pContext);
		}
	}
	return 0;
}

CSocketServer::CSocketServer()
{
	bIsInit = false;
}
