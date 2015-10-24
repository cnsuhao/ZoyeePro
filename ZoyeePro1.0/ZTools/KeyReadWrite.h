//--------------------------------------
//  文件路径： D:\Zoyee\ZoyeePro\ZoyeePro1.0\ZTools\KeyReadWrite.h
//  文件功能：
//
//  创建时间： 2015-10-24 10:01:31
//  author:		Zoyee
//  修改时间
//
#pragma once
#include "ikeycore.h"

//原则 : 写永远优先读, 可以读饥饿不能写饥饿

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
		void WriteLock();
		void WriteUnLock();
		void ReadLock();

	private:
		int m_nWaitWriter;
		int m_nWriterCount;
		int m_nReadCount;
		bool m_bWriteType;
		void* pCriSection;
		void* hMutex;
		void* hRead;
		void* hWrite;
		void* hEvent[2];		

		class CSLocker//自动释放CriticalSection辅助类
		{
		public:
			CSLocker(CKeyReadWrite* pThis);
			~CSLocker();
		private:
			CKeyReadWrite* m_pThis;
		};
	};
}
