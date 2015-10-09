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
		emContextAction emAction;
	}; 

	class INetworkCtrl
	{
	public:
		INetworkCtrl();
		~INetworkCtrl();

		virtual int Run();
		virtual int Pause();
		virtual int Resume();
		virtual int Stop();
	};

	class INetworkBase
	{
	public:
		static INetworkBase* Create(INetworkCallback* pCallback);
		virtual void Print() = 0;
		//static void Release(INetworkBase* pNetworkBase);
		//virtual CContext* Init(const char* pDesc, int nNetworkType, int nProtocol = TCP);
		//virtual int UnInit();

		//virtual int Send(const char* pszbuff, const int nLen, const CContext* pContext);
		//virtual CContext* Connect(CContext* pDesc);
		//virtual int DisConnect();
		//virtual int DisConnect(const CContext* pContext);// kick
	private:
		INetworkCtrl* pNetworkCtrl;
		INetworkCallback* m_pCallback;
	};

	class ZNetwork CNetwork
	{
	public:
		static CNetwork* Instance();
		static void ReleaseInstance();

		CNetwork* Create();
		void Release(CNetwork* pNetwork);

		INetworkBase* CreateNetworkBase(INetworkCallback* pCallback);
	private:
		CNetwork();
		~CNetwork();
		static CNetwork* pInstance;
	};
}