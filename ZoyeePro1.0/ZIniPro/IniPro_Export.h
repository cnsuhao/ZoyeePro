// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZINIPRO_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZINIPRO_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZINIPRO_EXPORTS
#define ZINIPRO_API __declspec(dllexport)
#else
#define ZINIPRO_API __declspec(dllimport)
#endif

#ifndef __INI_PRO_EXPORT_H__
#define __INI_PRO_EXPORT_H__

#define ZIniProExport ZINIPRO_API

#include <vector>
#include <map>
#include <string>

#define MaxPerLine 1024
namespace Ini_Pro
{
	typedef std::vector<std::string> arrayString;
	typedef std::pair<std::string, std::string> Couple;
	typedef std::vector<std::pair<std::string, std::string>> arrayCouple;
	typedef std::map<std::string, arrayCouple> tableData;

	class iIniPro
	{
	public:
		virtual iIniPro* Load(const char* pFile, bool bIfNotExistCreate = true) = 0;
		virtual bool Save(const char* pFile = 0) = 0;
		virtual int GetSections(arrayString& vecSection) = 0;
		virtual int GetKeys(const std::string strSection, arrayString& vecKeys) = 0;
		virtual std::string GetValueStr(const std::string strSection, const std::string strKey) = 0;
		virtual bool GetValueIni(const std::string strSection, const std::string strKey, __out int nRes) = 0;
		virtual bool GetValueFloat(const std::string strSection, const std::string strKey, __out float fRes) = 0;
		virtual bool GetValueBoolen(const std::string strSection, const std::string strKey, __out bool bRes) = 0;

	protected:
		tableData m_data;
	};
}

extern "C" 
{
	ZIniProExport Ini_Pro::iIniPro* CreateIniPro(const char* pFile, bool bCreateIfNotExist = true);
	ZIniProExport void ReleaseIniPro(Ini_Pro::iIniPro* pPro);
};
#endif

//extern ZINIPRO_API int nZIniPro;
//
//ZINIPRO_API int fnZIniPro(void);
