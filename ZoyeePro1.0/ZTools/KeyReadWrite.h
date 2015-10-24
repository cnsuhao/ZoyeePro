//--------------------------------------
//  �ļ�·���� D:\Zoyee\ZoyeePro\ZoyeePro1.0\ZTools\KeyReadWrite.h
//  �ļ����ܣ�
//
//  ����ʱ�䣺 2015-10-24 10:01:31
//  author:		Zoyee
//  �޸�ʱ��
//
#pragma once
#include "ikeycore.h"

//ԭ�� : д��Զ���ȶ�, ���Զ���������д����

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

		class CSLocker//�Զ��ͷ�CriticalSection������
		{
		public:
			CSLocker(CKeyReadWrite* pThis);
			~CSLocker();
		private:
			CKeyReadWrite* m_pThis;
		};
	};
}
