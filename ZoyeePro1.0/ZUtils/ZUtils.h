// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZUTILS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZUTILS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZUTILS_EXPORTS
#define ZUTILS_API __declspec(dllexport)
#else
#define ZUTILS_API __declspec(dllimport)
#endif

#ifndef __ZUTILS_H__
#define __ZUTILS_H__

namespace ZoyeePro10
{
#define ZUtils ZUTILS_API

	class ZUtils CList
	{
	public:
		CList();
		int Insert(void* pElement);
		void* First();
		void* Last();
		void* Next();
		void* Next(CList* pNode);
		void* Back();
		void* Back(CList* pNode);
		
	private:
		CList* pPreNode;
		CList* pNextNode;
	};

	class ITask
	{
	public:
		virtual int Run() = 0;
	};

	class ZUtils CSimpleThreadPool
	{
	public:	 

	};

}

#endif