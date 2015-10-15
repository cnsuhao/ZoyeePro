#include "stdafx.h"
#include "SocketClient.h"
#include "SocketBase.h"

#define MAXBUFFSIZE 1024

CSocketClient::CSocketClient(void)
{
	m_bIsInit = false;
	SetIsConnectd(false);
	m_sockCli = INVALID_SOCKET;
	m_pContext = NULL;
}


CSocketClient::~CSocketClient(void)
{
	m_sockCli = INVALID_SOCKET;
}

CContext* CSocketClient::Init( const char* pDesc, int nProtocol /*= TCP*/ )
{
	if (m_bIsInit)
	{
		m_pContext->pszBuff = "已经初始化过, 无法再次初始化";
		m_pContext->CalcBuffStrLen();
		m_pCallback->OnMSG(m_pContext);
		return m_pContext;
	}
	strcpy(&szDesc[0], pDesc);
	//m_sockCli = CSocketBase::Instance()->CreateConnection(pDesc, false, nProtocol);
	//if (m_sockCli != INVALID_SOCKET)
	//{
	//	SetIsConnectd(true);
	//}
	m_nProtocol = nProtocol;
	m_phThread = new HANDLE[1];
	m_nThreadSize = 1;
	m_bIsInit = true;
	m_phThread[0] = CreateThread(0, 0, workThread, this, 0, 0);
	return nullptr;
}

int CSocketClient::UnInit()
{
	return 0;
}

int CSocketClient::Send( const char* pszbuff, const int nLen, CContext* pContext )
{
	return nLen;
}

CContext* CSocketClient::Connect( CContext* pDesc )
{
	if (GetIsConnectd())
	{
		return m_pContext;
	}
	CContext* pContext = new CContext;
	pContext->pszDesc = new char[pDesc->nLen + 1];
	strcpy(pContext->pszDesc, pDesc->pszDesc);
	pContext->_c = CSocketBase::Instance()->CreateConnection(pContext->pszDesc, false, m_nProtocol);
	if (pContext->_c != INVALID_SOCKET)
	{
		pContext->pszBuff = "连接成功";
		pContext->CalcBuffStrLen();
		m_pCallback->OnMSG(pContext);
		m_pContext = pContext;
		SetIsConnectd(true);
	}
	else
	{
		pContext->pszBuff = NULL;
		pContext->Release();
		pContext = NULL;
	}
	
	return m_pContext;
}

int CSocketClient::DisConnect()
{
	return 0;
}

int CSocketClient::DisConnect( CContext* pContext )
{
	printNoSurport("CSocketClient::DisConnect(1)");
	return 0;
}

DWORD WINAPI CSocketClient::workThread( void* lpParam )
{
	CSocketClient* pThis = (CSocketClient*)lpParam;
	
	SOCKET s = pThis->m_sockCli;
	int nLen = 0;
	char szBuff[MAXBUFFSIZE] = {0};
	while (true)
	{		
		if (nLen <= 0)
		{
			CSocketBase::Close(pThis->m_sockCli);
			pThis->m_sockCli =CSocketBase::Instance()->CreateConnection(pThis->szDesc, false, pThis->m_nProtocol);
			if (pThis->m_pContext)
			{
				pThis->m_pContext->Release();
			}
			
			if (pThis->m_sockCli == INVALID_SOCKET)
			{
				Sleep(10);
				continue;
			}
			else
			{
				pThis->m_pContext = new CContext;
				pThis->m_pContext->emAction = ON_SYSTEM;
				pThis->m_pContext->_c = pThis->m_sockCli;
				pThis->m_pContext->pszBuff = "重连成功!";
				pThis->m_pContext->CalcBuffStrLen();
				pThis->m_pCallback->OnMSG(pThis->m_pContext);
				pThis->m_pContext->pszBuff = NULL;
			}
		}
		nLen = recv(pThis->m_sockCli, szBuff, MAXBUFFSIZE - 1, 0);
		pThis->m_pContext->pszBuff = szBuff;
		pThis->m_pContext->pszBuff[nLen] = 0;
		pThis->m_pContext->nLen = nLen;
		pThis->m_pCallback->OnMSG(pThis->m_pContext);		
		pThis->m_pContext->pszBuff = NULL;
	}
	return 0;
}
