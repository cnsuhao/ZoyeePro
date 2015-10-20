// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZSYSTEMCTRL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZSYSTEMCTRL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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