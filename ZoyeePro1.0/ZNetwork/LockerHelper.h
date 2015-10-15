#pragma once

#include <windows.h>

namespace ZoyeePro10
{
	class CKey
	{
	public:
		CKey();
		~CKey();
		CRITICAL_SECTION cs;
	};
	class CMutexLocker
	{
	public:
		CMutexLocker(CKey& key);
		~CMutexLocker();
		CKey& m_key;
	};
}

