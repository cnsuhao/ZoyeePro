#include "stdafx.h"
#include "LockerHelper.h"

ZoyeePro10::CKey::CKey()
{
	InitializeCriticalSection(&cs);
}

ZoyeePro10::CKey::~CKey()
{
	DeleteCriticalSection(&cs);
}

ZoyeePro10::CMutexLocker::CMutexLocker( CKey& key ) : m_key(key)
{
	EnterCriticalSection(&m_key.cs);
}

ZoyeePro10::CMutexLocker::~CMutexLocker()
{
	LeaveCriticalSection(&m_key.cs);
}
