#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
#include "../ZTools/ZTools.h"
#pragma comment(lib, "../output/debug/ztools.lib")

using namespace ZoyeePro10;
void write(void* p);
void read(void* p);

IKeyManage key(RWLock);
ILock lock(key);
int i = -1;
static string t1[2] = {"1", "w"};
static string t2[2] = {"2", "w"};
static string t3[2] = {"3", "r"};
static string t4[2] = {"4", "r"};
int main()
{


	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)write, &t1, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)write, &t2, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)write, &t3, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)write, &t4, 0, 0);

	for (;;)
	{
		cin >> i;
	}
}

void write( void* p )
{
	string* str = (string*)p;
	string id = str[0];
	string action =str[1];
	bool bRead = (action == "w");
	bool bIsLocked = false;
	for (;;)
	{		
		if (!bIsLocked)		
		{
			lock.Lock(bRead);
			bIsLocked = true;
		}
		
		Sleep(1000);		
		printf("[%s][%s]\n", action.c_str(), id.c_str());	
		if (atoi(id.c_str()) == i)
		{
			if (bIsLocked)
			{
				lock.UnLock(bRead);
				bIsLocked = false;
			}
		}
		if (i == 0 && bRead == false)
		{
			if (bIsLocked)
			{
				lock.UnLock(bRead);
				bIsLocked = false;
			}
			return;
		}
	}
}
