// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZSYSTEMCTRL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZSYSTEMCTRL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ZSYSTEMCTRL_EXPORTS
#define ZSYSTEMCTRL_API __declspec(dllexport)
#else
#define ZSYSTEMCTRL_API __declspec(dllimport)
#endif
#ifndef __ZSYSTEMCTRL_H__
#define __ZSYSTEMCTRL_H__
namespace ZoyeePro10
{
	#define  ZSYSTEM ZSYSTEMCTRL_API
	class ZSYSTEM CSystemInfo
	{
	public:
		void Release();
		CSystemInfo();
		char** arrIP;
		int nIpCount;

		char* pHostName;		
	};

	class ZSYSTEM CModule
	{
	public:
		CModule();
		void Release();
		char* pDirPath;
	};

	class ZSYSTEM CRegTools
	{
	public:
		static CRegTools* Instance();
		static void Release();
		static bool QueryValue(const char* pPath, const char* pKey, char* pValueOut);
		static bool WriteValue(const char* pPath, const char* pKey, char* pValue, int nType);		
	private:
		CRegTools();
		static CRegTools* m_ptrInstance;
	};

}


#endif