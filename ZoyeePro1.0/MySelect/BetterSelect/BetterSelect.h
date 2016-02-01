// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� BETTERSELECT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BETTERSELECT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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