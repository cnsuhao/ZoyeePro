#ifndef __INI_PRO_H__
#define __INI_PRO_H__ 
#include "IniPro_export.h"
#include <fstream>


namespace Ini_Pro
{
	class CIniPro : public Ini_Pro::iIniPro
	{
	public:
		virtual iIniPro* Load(const char* pFile, bool bIfNotExistCreate = true);
		virtual bool Save(const char* pFile = 0);
		virtual int GetSections(arrayString& vecSection);
		virtual int GetKeys(const std::string strSection, arrayString& vecKeys);
		virtual std::string GetValueStr(const std::string strSection, const std::string strKey);
		virtual bool GetValueIni(const std::string strSection, const std::string strKey, __out int nRes);
		virtual bool GetValueFloat(const std::string strSection, const std::string strKey, __out float fRes);
		virtual bool GetValueBoolen(const std::string strSection, const std::string strKey, __out bool bRes);
	private:
		std::fstream fs;
		char szFileName[1024];
		void analysis();
		void trim(const std::string strSrc, __out std::string& strRes, const char cTrim = ' ');
		bool splitKeyValue(const std::string strSrc, __out std::string& strKey, __out std::string& strValue, const char cSplit = '=');
	};
}

#endif