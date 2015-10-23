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

}

ZoyeePro10::CKeyReadWrite::~CKeyReadWrite( void )
{
	CLOSEHANDLE(hMutex);
	CLOSEHANDLE(hRead);
	CLOSEHANDLE(hWrite);
}

void ZoyeePro10::CKeyReadWrite::Lock( bool bIsReadLock /*= false*/ )
{

}

void ZoyeePro10::CKeyReadWrite::UnLock( bool bIsReadLock /*= false*/ )
{

}
