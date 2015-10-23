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

	protected:
		int AddWriter();
		int RemoveWriter();
		bool TryWriteLock();
		bool TryReadLock();

	private:
		void lockcs();
		void unlockcs();
		int m_nWriterCount;
		int m_nReadCount;
		void* pCriSection;
		void* hMutex;
		void* hRead;
		void* hWrite;
		void* hEvent[2];		
	};
}
