#pragma once
#include "ikeycore.h"
#include <Windows.h>

namespace ZoyeePro10
{
	class CKeyCriSetion : public IKeyCore
	{
	public:
		CKeyCriSetion(void);
		virtual ~CKeyCriSetion(void);
		void Lock(bool bIsReadLock = false);
		void UnLock(bool bIsReadLock = false);
	private:
		CRITICAL_SECTION cs;
	};
}

