#pragma once
#include "ikeycore.h"

namespace ZoyeePro10
{
	class CKeyReadWrite :	public IKeyCore
	{
	public:
		CKeyReadWrite(void);
		virtual ~CKeyReadWrite(void);
		void Lock(bool bIsReadLock = false);
		void UnLock(bool bIsReadLock = false);
	private:
		int AddWriter();
		int RemoveWriter();
		bool TryWriteLock();
		bool TryReadLock();

		int m_nWriterCount;
		int m_nReadCount;
		void* hMutex;
		void* hRead;
		void* hWrite;
		void* hEvent[2];		
	};
}
