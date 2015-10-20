// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZUTILS_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZUTILS_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
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