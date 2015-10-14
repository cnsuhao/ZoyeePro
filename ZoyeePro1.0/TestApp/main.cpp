#include <iostream>
using namespace std;

#include "../ZNetwork/ZNetwork.h"
using namespace ZoyeePro10;
#ifdef _DEBUG
#pragma comment(lib, "../output/debug/znetwork.lib")
#else
#pragma comment(lib, "../output/release/znetwork.lib")
#endif

#include <Windows.h>

class CNetworkCallback : public INetworkCallback
{
	int OnMSG(const CContext* pContext);
};

int CNetworkCallback::OnMSG( const CContext* pContext )
{
	printf("[recv] : \"%s\"\n", pContext->pszBuff);
	return 0;
}

int main()
{
	INetworkModel *ptr = CNetwork::CreateNetworkBase(NET_ONEWAY_SRV, new CNetworkCallback);
	ptr->Init("127.0.0.1:8888");

	while (true)
	{
		Sleep(10);
	}
}