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