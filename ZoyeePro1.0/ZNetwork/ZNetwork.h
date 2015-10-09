// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZNETWORK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZNETWORK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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