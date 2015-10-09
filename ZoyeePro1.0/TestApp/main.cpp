#include <iostream>
using namespace std;

#include "../ZNetwork/ZNetwork.h"
using namespace ZoyeePro10;
#ifdef _DEBUG
#pragma comment(lib, "../output/debug/znetwork.lib")
#else
#pragma comment(lib, "../output/release/znetwork.lib")
#endif

int main()
{
	CNetwork* work = CNetwork::Instance();
	work->CreateNetworkBase(NULL)->Print();
}