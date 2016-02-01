//#include <iostream>
//#include <WinSock2.h>
//
//#pragma comment(lib, "ws2_32.lib")
//
//#define HostIP "127.0.0.1"
//#define HostPort 33333
//
//SOCKET acceptSocket;
//
//
//timeval tv;
//int nSize;
//int nIndex;
//int nLen;
//int nRecvLen;
//sockaddr_in addr;
//SOCKET s ;
//int Work(void* pParam)
//{
//	fd_set fdRead, fdSocket;
//
//	FD_ZERO(&fdRead);
//	FD_ZERO(&fdSocket);
//	FD_SET(s, &fdSocket);
//	DWORD dwThreadID = GetCurrentThreadId();
//	nLen = sizeof(addr);
//	char sz[1024];
//	while(1)
//	{		
//		FD_ZERO(&fdRead);
//		fdRead = fdSocket;
//		//tv.tv_sec = 2;//2 second return
//		//tv.tv_usec = 0;
//		nIndex = select(0, &fdRead, NULL, NULL, /*&tv*/NULL);
//
//		if(FD_ISSET(s, &fdRead))
//		{
//			acceptSocket = accept(s, (sockaddr*)&addr, &nLen);
//			if (acceptSocket != INVALID_SOCKET)
//			{
//				FD_SET(acceptSocket, &fdSocket);
//				printf("[%d][%d][accept]\n", dwThreadID, acceptSocket);
//				continue;
//			}
//		}
//
//		for (int i = 0; i < fdSocket.fd_count; i++)
//		{
//			if (FD_ISSET(fdSocket.fd_array[i], &fdRead))
//			{
//				nRecvLen = recv(fdSocket.fd_array[i], sz, 1024, 0);
//				switch(nRecvLen)
//				{
//				case -1:
//					continue;
//				case 0:
//					printf("[%d][disconnect]\n", fdSocket.fd_array[i]);
//					closesocket(fdSocket.fd_array[i]);
//					FD_CLR(fdSocket.fd_array[i], &fdSocket);
//					continue;
//				default:
//					break;
//				}
//				sz[nRecvLen] = 0;
//				printf("[%d][%d][%s]\n", dwThreadID, fdSocket.fd_array[i], sz);
//			}
//		}
//	}
//	return 0;
//}
//
//
//
//int main()
//{
//	WSAData wsaData;
//	WSAStartup(0x0202, &wsaData);
//
//	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	sockaddr_in SOCK_IN;
//	SOCK_IN.sin_family = AF_INET;
//	SOCK_IN.sin_addr.S_un.S_addr = inet_addr(HostIP);
//	SOCK_IN.sin_port = htons(HostPort);
//
//	int nRes = bind(s, (sockaddr*)&SOCK_IN, sizeof(SOCK_IN));
//	nRes = listen(s, 5);
//
//	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Work, NULL, 0, 0);
//	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Work, NULL, 0, 0);
//	while(1)
//	{
//		Sleep(100000);
//	}
//}

#include "../BetterSelect/BetterSelect.h"
#pragma comment(lib, "../output/debug/BetterSelect.lib")

#include <iostream>
#include <Windows.h>

class CCallback : public nsSelect::ICallback
{
public:
	virtual void OnMessageRecv(const char* pBuff, const int nLen, unsigned int nSocket, const int nType);
};

void CCallback::OnMessageRecv( const char* pBuff, const int nLen, unsigned int nSocket, const int nType )
{
	printf("[%d][%s]\n", nSocket, pBuff);
}

int main()
{
	nsSelect::ISelectModel* pModel = CreateSelectModel(new CCallback, "127.0.0.1", 9998);
	while (1)
	{
		Sleep(1000);
	}
}
