// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZSYSTEM_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZSYSTEM_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ZSYSTEM_EXPORTS
#define ZSYSTEM_API __declspec(dllexport)
#else
#define ZSYSTEM_API __declspec(dllimport)
#endif

#ifndef __ZSYSTEM_H__
#define __ZSYSTEM_H__


namespace ZoyeePro10
{
#define ZSystem ZSYSTEM_API

#define INT_TYPE 0
#define STR_TYPE 1

class ZSystem CCpuInfo
{
public:
	CCpuInfo();
	int nCoreCount;
	//想到什么再补充
};

class ZSystem CHDInfo
{
public:
	CHDInfo();
	int nFree;
	int nMax;
	char szName[64];
};

class ZSystem CHardwareInfo
{
public:
	CHardwareInfo();
	~CHardwareInfo();

	CHDInfo* GetHDInfo(int& nCount);
	CCpuInfo* GetCpuInfo(int& nCount);

private:
	CHDInfo* m_pHdInfo;
	CCpuInfo* m_pCpuInfo;
	int m_nCpuCount;
	int m_nHDCount;
};

ZSystem bool IsOS_X64();
ZSystem int GetValueFromReg(char* lpSubKey, char* pRes, int nType = INT_TYPE, char* pHKEY = "HKEY_CURRENT_USER");
ZSystem int CmdOutputByPipe(char* cmd, char* res);//可以把控制台的打印输出到res上, 但会等待执行完毕函数才返回
ZSystem CHardwareInfo GetHardwareInfo();

}

#endif