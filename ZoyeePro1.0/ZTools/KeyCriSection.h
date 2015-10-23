#pragma once
#include "ikeycore.h"
#include <Windows.h>

namespace ZoyeePro10
{
	class CKeyCriSection : public IKeyCore
	{
	public:
		CKeyCriSection(void);
		virtual ~CKeyCriSection(void);
		void Lock(bool bIsReadLock = false);
		void UnLock(bool bIsReadLock = false);
	private:
		CRITICAL_SECTION cs;
	};
}

