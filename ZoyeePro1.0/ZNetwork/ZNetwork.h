// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZNETWORK_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZNETWORK_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ZNETWORK_EXPORTS
#define ZNETWORK_API __declspec(dllexport)
#else
#define ZNETWORK_API __declspec(dllimport)
#endif

#ifndef __ZOYEE_ZNETWORK_H__
#define __ZOYEE_ZNETWORK_H__


namespace ZoyeePro10
{
#define ZNetwork ZNETWORK_API
#define TCP 0

#define NET_SHAREMEM_SRV	0x1000
#define NET_PIPE_SRV			0x1001
#define NET_IOCP_SRV			0x1002
#define NET_ONEWAY_SRV		0x1003

#define NET_SHAREMEM_CLI	0x2000
#define NET_PIPE_CLI			0x2001
#define NET_SOCKCLIENT		0x2002



	enum emContextAction
	{
		ON_ACCEPT,
		ON_CONNECT,
		ON_KICK,
		ON_DISCONNECT,
		ON_SEND,
		ON_RECV,
		ON_INIT,
		ON_UNINIT,
		ON_RUN,
		ON_STOP,
		ON_PAUSE,
		ON_RESUEM,
		//---------------------------------
		ON_SYSTEM = 0x0100,
		ON_ERROR,
	};

	class CContext;
	class INetworkModel;
	class CNetwork;

	class INetworkCallback
	{
	public:
		virtual int OnMSG(const CContext* pContext) = 0;
	};
	
	class ZNetwork CContext
	{
	public:		
		char* pszBuff;
		int nLen;
		char* pszDesc;
		void* pHandle;
		unsigned int _c;
		unsigned int _s;
		emContextAction emAction;
		void Release();
		void CalcBuffStrLen();
	}; 

	class INetworkModel
	{
		friend class CNetwork;
	public:
		void SetCallback(INetworkCallback* pCallback);
		virtual ~INetworkModel();
		virtual CContext* Init(const char* pDesc, int nProtocol = TCP) = 0;
		virtual int UnInit() = 0;

		virtual int Send(const char* pszbuff, const int nLen, CContext* pContext) = 0;
		virtual CContext* Connect(CContext* pDesc) = 0;
		virtual int DisConnect() = 0;
		virtual int DisConnect(CContext* pContext) = 0;// kick
	protected:
		INetworkCallback* m_pCallback;
		void** m_phThread;
		int m_nThreadSize;
	};

	class ZNetwork CNetwork
	{
		friend class INetworkModel;
	public:
		static CNetwork* Instance();
		static void ReleaseInstance();

		static INetworkModel* CreateNetworkBase(int nNetworkType,  INetworkCallback* pCallback);
		static void ReleaseINetworkModel(INetworkModel* pNetworkModel);

		static int Pause(INetworkModel* pModel);
		static int Resume(INetworkModel* pModel);

	private:
		CNetwork();
		~CNetwork();
		static CNetwork* pInstance;
	};

	void printNoSurport(const char* pFuncName);
}

#endif