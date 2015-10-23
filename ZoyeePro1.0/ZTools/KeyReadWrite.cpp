#include "StdAfx.h"
#include "KeyReadWrite.h"
#include <Windows.h>

#define CLOSEHANDLE(h) if(h != nullptr){CloseHandle(h);h = nullptr;}


ZoyeePro10::CKeyReadWrite::CKeyReadWrite( void ) :
	hMutex(nullptr),
	hRead(nullptr),
	hWrite(nullptr),
	m_nWriterCount(0),
	m_nReadCount(0)
{
	pCriSection = new CRITICAL_SECTION;
	::InitializeCriticalSection((CRITICAL_SECTION*)pCriSection);
}

ZoyeePro10::CKeyReadWrite::~CKeyReadWrite( void )
{
	CLOSEHANDLE(hMutex);
	CLOSEHANDLE(hRead);
	CLOSEHANDLE(hWrite);
	::DeleteCriticalSection((CRITICAL_SECTION*)pCriSection);
}

void ZoyeePro10::CKeyReadWrite::Lock( bool bIsReadLock /*= false*/ )
{

}

void ZoyeePro10::CKeyReadWrite::UnLock( bool bIsReadLock /*= false*/ )
{

}

void ZoyeePro10::CKeyReadWrite::lockcs()
{
	::EnterCriticalSection((CRITICAL_SECTION*)pCriSection);
}

void ZoyeePro10::CKeyReadWrite::unlockcs()
{
	::LeaveCriticalSection((CRITICAL_SECTION*)pCriSection);
}

int ZoyeePro10::CKeyReadWrite::AddWriter()
{
	lockcs();
	m_nWriterCount++;
	unlockcs();
	
	ResetEvent(hRead);	
	return m_nWriterCount;
}

int ZoyeePro10::CKeyReadWrite::RemoveWriter()
{
	lockcs();
	m_nWriterCount--;
	unlockcs();

	ReleaseMutex(hMutex);
	SetEvent(hRead);
	return m_nWriterCount;
}

bool ZoyeePro10::CKeyReadWrite::TryWriteLock()
{
	lockcs();
	if (m_nWriterCount > 0)
	{
		unlockcs();
		return false;
	}
	unlockcs();
	return true;
}

bool ZoyeePro10::CKeyReadWrite::TryReadLock()
{

	return true;
}
