// ZNetwork.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ZNetwork.h"
using namespace ZoyeePro10;

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



CNetwork* ZoyeePro10::CNetwork::pInstance = nullptr;

class Zbase : public INetworkBase
{
public:
	void Print()
	{
		printf("bb");
	}
};


INetworkBase* ZoyeePro10::CNetwork::CreateNetworkBase( INetworkCallback* pCallback )
{
	return new Zbase;
}