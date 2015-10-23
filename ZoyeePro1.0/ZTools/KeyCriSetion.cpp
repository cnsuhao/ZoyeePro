#include "StdAfx.h"
#include "KeyCriSetion.h"


ZoyeePro10::CKeyCriSetion::CKeyCriSetion(void)
{
	::InitializeCriticalSection(&cs);
}


ZoyeePro10::CKeyCriSetion::~CKeyCriSetion(void)
{
	::DeleteCriticalSection(&cs);
}

void ZoyeePro10::CKeyCriSetion::Lock(bool bIsReadLock)
{
	::EnterCriticalSection(&cs);
}

void ZoyeePro10::CKeyCriSetion::UnLock(bool bIsReadLock)
{
	::LeaveCriticalSection(&cs);
}
