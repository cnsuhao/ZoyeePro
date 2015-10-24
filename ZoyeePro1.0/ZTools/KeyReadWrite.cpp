#include "StdAfx.h"
#include "KeyReadWrite.h"
#include <Windows.h>

#define CLOSEHANDLE(h) if(h != nullptr){CloseHandle(h);h = nullptr;}


ZoyeePro10::CKeyReadWrite::CKeyReadWrite( void ) :
	hMutex(nullptr),
	hRead(nullptr),
	hWrite(nullptr),
	m_nWriterCount(0),
	m_nReadCount(0),
	m_nWaitWriter(0)
{
	pCriSection = new CRITICAL_SECTION;
	::InitializeCriticalSection((CRITICAL_SECTION*)pCriSection);

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hRead = CreateEvent(NULL, FALSE, FALSE, NULL);
	hWrite = CreateEvent(NULL, FALSE, FALSE, NULL);
}

ZoyeePro10::CKeyReadWrite::~CKeyReadWrite( void )
{
	CLOSEHANDLE(hMutex);
	CLOSEHANDLE(hRead);
	CLOSEHANDLE(hWrite);
	::DeleteCriticalSection((CRITICAL_SECTION*)pCriSection);
	CRITICAL_SECTION* _pCriSection = (CRITICAL_SECTION*)pCriSection;
	delete _pCriSection;
	pCriSection = NULL;
}

void ZoyeePro10::CKeyReadWrite::Lock( bool bIsReadLock /*= false*/ )
{
	bIsReadLock ? ReadLock() : AddWriter();
}

void ZoyeePro10::CKeyReadWrite::UnLock( bool bIsReadLock /*= false*/ )
{
	bIsReadLock ? true : RemoveWriter();
}

int ZoyeePro10::CKeyReadWrite::AddWriter()
{
	ResetEvent(hWrite);
	ResetEvent(hRead);	
	WaitForSingleObject(hMutex, INFINITE);
	{
		CSLocker lock(this);
		m_nWaitWriter++;
	}
	//挂起 读事件和写事件	
	printf("\n[Lock-W][waiting-w is %d]\n", m_nWaitWriter);
	return m_nWaitWriter;
}

int ZoyeePro10::CKeyReadWrite::RemoveWriter()
{
	CSLocker lock(this);
	m_nWaitWriter--;//减 "写" 等待数
	if (m_nWaitWriter <= 0)//没有写 等待
	{		
		SetEvent(hRead);//可读		
	}
	if (m_nWaitWriter > 0)//还有写 等待 , 不可读
	{
		ResetEvent(hRead);//不可读	
	}	
	SetEvent(hWrite);//可写
	ReleaseMutex(hMutex);//释放线程占用
	printf("\n[UnLock-W][waiting-w is %d]\n", m_nWaitWriter);
	return m_nWriterCount;
}

void ZoyeePro10::CKeyReadWrite::WriteLock()
{
	AddWriter();
}

void ZoyeePro10::CKeyReadWrite::WriteUnLock()
{
	RemoveWriter();
}

void ZoyeePro10::CKeyReadWrite::ReadLock()
{
	printf("\n[Lock-R][waiting-w is %d]\n", m_nWaitWriter);
	HANDLE h[2];
	h[0] = hWrite;
	h[1] = hRead;
	WaitForMultipleObjects(2, h, TRUE, INFINITE);//同时为真, 否则堵塞
}

ZoyeePro10::CKeyReadWrite::CSLocker::CSLocker( CKeyReadWrite* pThis ):
	m_pThis(pThis)
{
	::EnterCriticalSection((CRITICAL_SECTION*)m_pThis->pCriSection);
}

ZoyeePro10::CKeyReadWrite::CSLocker::~CSLocker()
{
	::LeaveCriticalSection((CRITICAL_SECTION*)m_pThis->pCriSection);
}
