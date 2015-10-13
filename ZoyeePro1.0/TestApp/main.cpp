#include <iostream>
using namespace std;

//#include "../ZNetwork/ZNetwork.h"
//using namespace ZoyeePro10;
//#ifdef _DEBUG
//#pragma comment(lib, "../output/debug/znetwork.lib")
//#else
//#pragma comment(lib, "../output/release/znetwork.lib")
//#endif

#include <Windows.h>

char* p;
void seterror(const char* ps)
{
	p = (char*)ps;
}

int main()
{
	seterror("hello");
	seterror("123");
}