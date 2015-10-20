// ZNetwork.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZNetwork.h"
#include "IocpServer.h"
#include "SocketServer.h"
#include "SocketClient.h"
#include "SelectServer.h"

using namespace ZoyeePro10;
#define FreeChars(str) if(str != NULL){delete str; str = nullptr;}

CNetwork* ZoyeePro10::CNetwork::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new CNetwork;
	}
	return pInstance;
}

ZoyeePro10::CNetwork::CNetwork()
{

}

int ZoyeePro10::CNetwork::Pause( INetworkModel* pModel )
{
	for (int i = 0; i < pModel->m_nThreadSize; i++)
	{
		::SuspendThread(pModel->m_phThread[i]);
	}
	return pModel->m_nThreadSize;
}

int ZoyeePro10::CNetwork::Resume( INetworkModel* pModel )
{
	for (int i = 0; i < pModel->m_nThreadSize; i++)
	{
		::ResumeThread(pModel->m_phThread[i]);
	}
	return pModel->m_nThreadSize;
}

INetworkModel* ZoyeePro10::CNetwork::CreateNetworkBase( int nNetworkType, INetworkCallback* pCallback )
{
	INetworkModel* ptr = nullptr;
	switch (nNetworkType)
	{
	case NET_SHAREMEM_SRV:
		break;
	case NET_PIPE_SRV:
		break;
	case NET_IOCP_SRV:
		ptr = new CIocpServer;
		ptr->SetCallback(pCallback);
		break;
	case NET_ONEWAY_SRV:
		ptr = new CSocketServer;
		ptr->SetCallback(pCallback);
		break;
	case NET_SELECT:
		ptr = new CSelectServer;
		ptr->SetCallback(pCallback);
		break;
	case NET_SHAREMEM_CLI:
		break;
	case NET_PIPE_CLI:
		break;
	case NET_SOCKCLIENT:
		ptr = new CSocketClient;
		ptr->SetCallback(pCallback);
		break;
	default:
		break;
	}
	return ptr;
}

CNetwork* ZoyeePro10::CNetwork::pInstance = nullptr;

void ZoyeePro10::printNoSurport( const char* pFuncName )
{
	printf("[%s]并没有实现, 原因大概是不需要!\n", pFuncName);
}


ZoyeePro10::INetworkModel::~INetworkModel()
{

}

void ZoyeePro10::INetworkModel::SetCallback( INetworkCallback* pCallback )
{
	m_pCallback = pCallback;
}

void ZoyeePro10::CContext::Release()
{
	FreeChars(pszBuff);
	FreeChars(pszDesc);
	delete this;
}

void ZoyeePro10::CContext::CalcBuffStrLen()
{
	nLen = strlen(pszBuff);
}

ZoyeePro10::CContext::CContext()
{
	pszBuff = NULL;
	pszDesc = NULL;
	pHandle = NULL;
	_c = _s = INVALID_SOCKET;
}

void ZoyeePro10::CContext::SetStaticBuff( const char* psz, emContextAction _emAction )
{
	pszBuff = (char*)psz;
	CalcBuffStrLen();
	emAction = _emAction;
}

void ZoyeePro10::CContext::ReleaseStatic()
{
	pszBuff = NULL;
	nLen = 0;
}
