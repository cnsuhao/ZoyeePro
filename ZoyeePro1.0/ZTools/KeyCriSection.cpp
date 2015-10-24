#include "StdAfx.h"
#include "KeyCriSection.h"


ZoyeePro10::CKeyCriSection::CKeyCriSection(void)
{
	::InitializeCriticalSection(&cs);
}


ZoyeePro10::CKeyCriSection::~CKeyCriSection(void)
{
	::DeleteCriticalSection(&cs);
}

void ZoyeePro10::CKeyCriSection::Lock(bool bIsReadLock)//互斥锁忽视参数
{
	::EnterCriticalSection(&cs);
}

void ZoyeePro10::CKeyCriSection::UnLock(bool bIsReadLock)//互斥锁忽视参数
{
	::LeaveCriticalSection(&cs);
}
