// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZTOOLS_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZTOOLS_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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
		IKeyManage(emKeyType nType = AutoCriSetion);//0, 自动解锁式cs, 1表示要手动解cs, 
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

	//----------------------------thread pool------------------------------------
	class ITask
	{
	public:
		virtual void Run(void* lpParam) = 0;
	};

	//----------------------------thread pool------------------------------------

	//----------------------------auto free template (include this h is enough ^_^)---------------------------
	template <class TObject>
	class CAutoPtr
	{
	public:
		CAutoPtr(TObject* ptr);
		~CAutoPtr();
		TObject* GetPtr();
	private:
		TObject* m_ptr;
	};

	template <class TObject> 
	ZoyeePro10::CAutoPtr<TObject>::CAutoPtr( TObject* ptr )
	{
		m_ptr = ptr;
	};

	template <class TObject> 
	ZoyeePro10::CAutoPtr<TObject>::~CAutoPtr()
	{
		delete m_ptr;
	};

	template <class TObject> 
	TObject* ZoyeePro10::CAutoPtr<TObject>::GetPtr()
	{
		return m_ptr;
	};
	//----------------------------auto free template (include this h is enough ^_^)---------------------------


	//class CAutoPtr
}

#endif