// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZTOOLS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZTOOLS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZTOOLS_EXPORTS
#define ZTOOLS_API __declspec(dllexport)
#else
#define ZTOOLS_API __declspec(dllimport)
#endif

#ifndef __ZTOOL_H__
#define __ZTOOL_H__

#define ZTools ZTOOLS_API

namespace ZoyeePro10
{
	//-----------------------------lock-------------------------------------------
	enum emKeyType
	{
		AutoCriSetion,
		ManualCriSetion,
		RWLock,//read - write lock
	};

	class IKeyCore;
	class ZTools IKeyManage
	{
	public:
		IKeyManage(emKeyType nType = AutoCriSetion);//0, �Զ�����ʽcs, 1��ʾҪ�ֶ���cs, 
		~IKeyManage();
		void Lock(bool bIsReadLock = false) const;
		void UnLock(bool bIsReadLock = false) const;
		const emKeyType nKeyType;
	protected:
		IKeyCore* pKeyCore;
	};

	class ZTools ILock
	{
	public:
		ILock(IKeyManage& keyMgr);
		~ILock();
		void Lock(bool bIsReadLock = false);
		void UnLock(bool bIsReadLock = false);
	private:
		const IKeyManage& m_keyMgr;
	};
	//-----------------------------lock-------------------------------------------

	class ITask
	{
	public:
		virtual void Run(void* lpParam) = 0;
	};

	

}

#endif