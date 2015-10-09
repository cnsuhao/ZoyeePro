#include <iostream>
using namespace std;

#include "../ZNetwork/ZNetwork.h"
using namespace ZoyeePro10;
#ifdef _DEBUG
#pragma comment(lib, "../output/debug/znetwork.lib")
#else
#pragma comment(lib, "../output/release/znetwork.lib")
#endif

class IClass
{
public:
	IClass();
	~IClass();
	virtual int test() = 0;
private:

};

IClass::IClass()
{
}

IClass::~IClass()
{
}

int IClass::test()
{
	return 10;
}

class SS : public IClass
{
public:
	//int test(){return 20;};
};

int main()
{

}