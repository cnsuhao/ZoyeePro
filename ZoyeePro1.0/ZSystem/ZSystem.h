// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZSYSTEM_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZSYSTEM_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
	//�뵽ʲô�ٲ���
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
ZSystem int CmdOutputByPipe(char* cmd, char* res);//���԰ѿ���̨�Ĵ�ӡ�����res��, ����ȴ�ִ����Ϻ����ŷ���
ZSystem CHardwareInfo GetHardwareInfo();

}

#endif