#include "StdAfx.h"
#include "SelectModel.h"
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class CThreadInfo
{
public:
	CThreadInfo(nsSelect::CSelectModel* pThis, nsSelect::CSocketArray* pSocketArray)
	{
		this->pThis = pThis;
		this->pSocketArray = pSocketArray;
	};
	nsSelect::CSelectModel* GetThis(){return pThis;};
	nsSelect::CSocketArray* GetSocketArray(){return pSocketArray;};	

protected:
	nsSelect::CSelectModel* pThis;
	nsSelect::CSocketArray* pSocketArray;
};


nsSelect::CSelectModel::CSelectModel( nsSelect::ICallback* pCallbackPtr ) : ISelectModel(pCallbackPtr)
{
	WSAData wsaData;
	WSAStartup(0x0202, &wsaData);
}

int nsSelect::CSelectModel::Send( const char* pBuff, const int nLen, unsigned int nSocket )
{	
	return send(nSocket, pBuff, nLen, 0);
}

bool nsSelect::CSelectModel::InitServer( const char* pHostIP, const int nPort )
{
	sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in SOCK_IN;
	SOCK_IN.sin_family = AF_INET;
	SOCK_IN.sin_addr.S_un.S_addr = inet_addr(pHostIP);
	SOCK_IN.sin_port = htons(nPort);

	if (bind(sockServer, (sockaddr*)&SOCK_IN, sizeof(SOCK_IN)) != 0)
	{
		strError = "bind fail";
		return false;
	}

	listen(sockServer, 10);
	hAccept = CreateThread(0, 0, AcceptThread, this, 0, 0);

	return true;
}

void nsSelect::CSelectModel::DisConnect( unsigned int nSocket )
{
	_LOCK_;
	std::list<CSocketArray*>::iterator iter = lstSocketArray.begin();
	for (; iter != lstSocketArray.end(); iter++)
	{
		if((*iter)->RemoveSocket(nSocket))
		{
			return;
		}
	}	
}

int nsSelect::CSelectModel::GetConnectCounts()
{
	_LOCK_;
	m_nCount = 0;
	std::list<CSocketArray*>::iterator iter = lstSocketArray.begin();
	for (; iter != lstSocketArray.end(); iter++)
	{
		m_nCount += (*iter)->GetSize();
	}
	return m_nCount;
}

const char* nsSelect::CSelectModel::GetLastError()
{
	return strError.c_str();
}

DWORD nsSelect::CSelectModel::WorkThread( void* pParam )
{
	CThreadInfo* pThreadInfo = (CThreadInfo*)pParam;
	CSelectModel* pThis = pThreadInfo->GetThis();
	CSocketArray* pSocketArray = pThreadInfo->GetSocketArray();
	fd_set* fd = (fd_set*)pSocketArray->GetFd();
	printf("[%d]CreateThread\n", GetCurrentThreadId());
	int nLen = -1;
	int nRes = 0;
	DWORD dwThreadID = GetCurrentThreadId();
	char szBuff[Max_buff_size] = {0};
	timeval tm;
	tm.tv_sec = 1;
	tm.tv_usec = 0;

	while(1)
	{
		pSocketArray->SetSelect(fd);		
		nRes = select(0, fd, NULL, NULL, &tm);

		if (pSocketArray->GetSize() == 0)
		{
			break;
		}

		if (nRes == 0)
		{
			continue;
		}
		if (nRes == -1)
		{
			printf("[%d] select error, errorCode=[%d]\n", GetCurrentThreadId(), ::WSAGetLastError());
		}

		for (int i = 0; i < fd->fd_count; i++)
		{
			if (FD_ISSET(fd->fd_array[i], fd))
			{
				nLen = recv(fd->fd_array[i], szBuff, Max_buff_size, 0);
				printf("[%d]", dwThreadID);
				switch(nLen)
				{
				case -1:
					pThis->m_pCallbackPtr->OnMessageRecv("error", 0, fd->fd_array[i], ErrorMsg);
					continue;
				case 0:
					pThis->m_pCallbackPtr->OnMessageRecv("disconnect", 0, fd->fd_array[i], SystemMsg);
					closesocket(fd->fd_array[i]);
					pSocketArray->RemoveSocket(fd->fd_array[i]);
					continue;
				default:
					szBuff[nLen] = 0;
					pThis->m_pCallbackPtr->OnMessageRecv(szBuff, nLen, fd->fd_array[i], NormalMsg);
					pThis->Send(szBuff, nLen, fd->fd_array[i]);
					break;
				}
			}
		}
	}	
	delete pThreadInfo;
	pThreadInfo = nullptr;
	pThis->RemoveSocketArray(pSocketArray);
	printf("[%d]Exit thread\n", GetCurrentThreadId());
	return 0;
}

DWORD WINAPI nsSelect::CSelectModel::AcceptThread( void* pParam )
{
	CSelectModel* pThis = (CSelectModel*)pParam;
	SOCKADDR_IN sockIn;
	int nLen = sizeof(sockIn);
	while(1)
	{
		SOCKET client = accept(pThis->sockServer, (sockaddr*)&sockIn, &nLen);
		pThis->PushToThread(client);
	}
	return 0;
}

int nsSelect::CSelectModel::PushToThread(unsigned int nSocket)
{
	_LOCK_;
	
	std::list<CSocketArray*>::iterator iter = lstSocketArray.begin();
	for (; iter != lstSocketArray.end(); iter++)
	{
		if ((*iter)->GetSize() < MaxArraySize)
		{
			(*iter)->AddSocket(nSocket);
			return lstSocketArray.size();
		}
	}
	fd_set* fd = new fd_set;
	CSocketArray* socketArray = new CSocketArray(fd);		
	socketArray->AddSocket(nSocket);
	lstSocketArray.push_back(socketArray);
	CThreadInfo* pThreadInfo = new CThreadInfo(this, socketArray);
	CreateThread(0, 0, WorkThread, pThreadInfo, 0, 0);
	return lstSocketArray.size();
}

void nsSelect::CSelectModel::RemoveSocketArray( CSocketArray* pSocketArray )
{
	_LOCK_;
	std::list<CSocketArray*>::iterator iter = lstSocketArray.begin();
	for (; iter != lstSocketArray.end(); iter++)
	{
		if ((*iter)->GetFd() == pSocketArray->GetFd())
		{
			delete *iter;
			lstSocketArray.erase(iter);
			return;
		}
	}
}

nsSelect::CSocketArray::CSocketArray(void* pFdSet)
{
	this->pFdSet = pFdSet;
	for (int i = 0; i < MaxArraySize; i++)
	{
		arraySocket[i] = 0;
	}
	nSize = 0;
}

bool nsSelect::CSocketArray::AddSocket( unsigned int nSocket )
{
	_LOCK_;
	for (int i = 0; i < MaxArraySize; i++)
	{
		if (arraySocket[i] == 0)
		{
			arraySocket[i] = nSocket;
			FD_SET(nSocket, pFdSet);
			nSize++;
			printf("[%d] accept!\n", nSocket);
			return true;
		}
	}
	return false;
}

bool nsSelect::CSocketArray::RemoveSocket( unsigned int nSocket )
{
	_LOCK_;
	for (int i = 0; i < MaxArraySize; i++)
	{
		if (arraySocket[i] == nSocket)
		{
			FD_CLR(arraySocket[i], pFdSet);
			arraySocket[i] = 0;
			nSize--;
			return true;
		}
	}
	return false;
}

void nsSelect::CSocketArray::SetSelect( void* pFdSet )
{
	_LOCK_;
	FD_ZERO(pFdSet);
	this->pFdSet = pFdSet;
	fd_set* fdRead = (fd_set*)pFdSet;
	for (int i = 0; i < nSize; i++)
	{
		FD_SET(arraySocket[i], fdRead);
	}
}

nsSelect::CSocketArray::~CSocketArray()
{
	fd_set* fd = (fd_set*)pFdSet;
	delete fd;
	fd = nullptr;
}
