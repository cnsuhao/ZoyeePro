// ZNetwork.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZNetwork.h"
#include "IocpServer.h"
#include "SocketServer.h"

using namespace ZoyeePro10;
#define FreeChars(str) if(str){delete str; str = nullptr;}

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
	case NET_PIPE_SRV:
	case NET_IOCP_SRV:
		ptr = new CIocpServer;
		ptr->SetCallback(pCallback);
		break;
	case NET_ONEWAY_SRV:
		ptr = new CSocketServer;
		ptr->SetCallback(pCallback);
	case NET_SHAREMEM_CLI:
	case NET_PIPE_CLI:
	case NET_SOCKCLIENT:
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
}

void ZoyeePro10::CContext::CalcBuffStrLen()
{
	nLen = strlen(pszBuff);
}
