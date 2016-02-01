// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BETTERSELECT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BETTERSELECT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef BETTERSELECT_EXPORTS
#define BETTERSELECT_API __declspec(dllexport)
#else
#define BETTERSELECT_API __declspec(dllimport)
#endif

#ifndef __BETTER_SELECT_H__
#define __BETTER_SELECT_H__

#define SELECT_EX_EXPORT BETTERSELECT_API
#define NormalMsg				0
#define SystemMsg				1
#define ErrorMsg				2

#define Max_buff_size 1024
#define MaxArraySize 63

#if MaxArraySize > 64
#error "MaxArraySize must be 1~64"
#endif

namespace nsSelect
{
	class ICallback
	{
	public:
		virtual void OnMessageRecv(const char* pBuff, const int nLen, unsigned int nSocket, const int nType) = 0;
	};

	class ISelectModel
	{
	public:
		ISelectModel(nsSelect::ICallback* pCallbackPtr);
		virtual int Send(const char* pBuff, const int nLen, unsigned int nSocket) = 0;
		virtual bool InitServer(const char* pHostIP, const int nPort) = 0;
		virtual void DisConnect(unsigned int nSocket) = 0;
		virtual int GetConnectCounts() = 0;
		virtual const char* GetLastError() = 0;
	protected:
		nsSelect::ICallback* m_pCallbackPtr;
		int m_nCount;
	};
}

extern "C" SELECT_EX_EXPORT nsSelect::ISelectModel* CreateSelectModel(nsSelect::ICallback* pCallbackPtr, const char* pHostIP, const int nPort);
extern "C" SELECT_EX_EXPORT void ReleaseSelectModel(nsSelect::ISelectModel* pModel);

#endif