#pragma once
#include "ZTools.h"

namespace ZoyeePro10
{
	class IKeyCore
	{
	public:
		IKeyCore();
		virtual ~IKeyCore(void);
		virtual void Lock(bool bIsReadLock = false) = 0;
		virtual void UnLock(bool bIsReadLock = false) = 0;
	};
}

