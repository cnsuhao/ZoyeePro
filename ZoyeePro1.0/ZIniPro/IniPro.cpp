#include "StdAfx.h"
#include "IniPro.h"
using namespace std;
namespace Ini_Pro
{
#define CheckValue(section, key) std::string strValue = GetValueStr(section, key); if(strValue == ""){ return false; } return strValue;

	iIniPro* CIniPro::Load( const char* pFile, bool bIfNotExistCreate)
	{
		strcpy(szFileName, pFile);
		fs.open(pFile, ios::in);
		do 
		{
			if ( ! fs)
			{
				//²»´æÔÚ
				if (bIfNotExistCreate)
				{
					fs.open(pFile, ofstream::out);
					fs.close();
					fs.open(pFile, ios::in);
					break;
				}
				delete this;
				return NULL;
			}
		} while (false);
		
		analysis();
		fs.close();
		return this;
	}

	int CIniPro::GetSections( arrayString& vecSection )
	{
		vecSection.clear();
		tableData::iterator iter = m_data.begin();
		for (; iter != m_data.end(); iter++)
		{
			vecSection.push_back(iter->first);
		}
		return 0;
	}

	int CIniPro::GetKeys( const std::string strSection, arrayString& vecKeys )
	{
		vecKeys.clear();
		tableData::iterator iter = m_data.find(strSection);
		if (iter != m_data.end())
		{
			for (int i = 0; i < iter->second.size(); i++)
			{
				vecKeys.push_back((iter->second)[i].first);
			}
		}
		return 0;
	}

	std::string CIniPro::GetValueStr( const std::string strSection, const std::string strKey )
	{		
		tableData::iterator iter = m_data.find(strSection);
		if (iter != m_data.end())
		{
			for (int i = 0; i < iter->second.size(); i++)
			{
				if (strKey == iter->second[i].first)
				{
					return iter->second[i].second;
				}
			}
		}
		return "";
	}

	bool CIniPro::GetValueIni( const std::string strSection, const std::string strKey, __out int nRes )
	{
		std::string strValue = GetValueStr(strSection, strKey);
		if (strValue == "")
		{
			return false;
		}
		nRes = atoi(strValue.c_str());
		return true;
	}

	bool CIniPro::GetValueFloat( const std::string strSection, const std::string strKey, __out float fRes )
	{
		std::string strValue = GetValueStr(strSection, strKey);
		if (strValue == "")
		{
			return false;
		}
		fRes = atof(strValue.c_str());
		return true;
	}

	bool CIniPro::GetValueBoolen( const std::string strSection, const std::string strKey, __out bool bRes )
	{
		std::string strValue = GetValueStr(strSection, strKey).c_str();
		if (strValue.length() == 4)
		{
			if ((strValue.at(0) == 'T' || strValue.at(0) == 't') &&
				(strValue.at(1) == 'R' || strValue.at(1) == 'r') &&
				(strValue.at(2) == 'U' || strValue.at(2) == 'u') &&
				(strValue.at(3) == 'E' || strValue.at(3) == 'e'))
			{
				bRes = true;
				return true;
			}
		}
		if (strValue.length() == 5)
		{
			if ((strValue.at(0) == 'F' || strValue.at(0) == 'f') &&
				(strValue.at(1) == 'A' || strValue.at(1) == 'a') &&
				(strValue.at(2) == 'L' || strValue.at(2) == 'l') &&
				(strValue.at(3) == 'S' || strValue.at(3) == 's') &&
				(strValue.at(4) == 'E' || strValue.at(4) == 'e'))
			{
				bRes = false;
				return true;
			}
		}
		return 0;
	}

	bool CIniPro::Save( const char* pFile /*= 0*/ )
	{
		char szSaveName[1024] = {0};
		if (pFile == NULL)
		{
			strcpy(szSaveName, szFileName);
		}
		else
		{
			strcpy(szSaveName, pFile);
		}
		fs.open(szSaveName, ofstream::out);
		tableData::iterator iter = m_data.begin();
		for (; iter != m_data.end(); iter++)
		{
			std::string strSection = "[" + iter->first + "]\n";
			fs << strSection;
			std::string strKey;
			std::string strValue;
			for (size_t i = 0; i < iter->second.size(); i++)
			{
				strKey = iter->second[i].first;
				strValue = iter->second[i].second;
				strKey = strKey + "=" + strValue + "\n";
				fs <<strKey;
			}
		}
		fs.flush();
		fs.close();
		return true;
	}

	void CIniPro::analysis()
	{
		m_data.clear();
		char szLine[MaxPerLine] = {0};
		std::string strSrc;
		std::string strSection;
		std::string strKey;
		std::string strValue;

		arrayCouple vecCouple;
		int nLen = -1;
		while ( ! fs.eof())
		{
			fs.getline(szLine, MaxPerLine);
			nLen = strlen(szLine);
			if (szLine[0] == '[' && szLine[nLen - 1] == ']')
			{
				char szSection[MaxPerLine] = {0};
				memcpy(szSection, &szLine[1], nLen - 2);
				strSection = szSection;
				m_data.insert(make_pair(strSection, vecCouple));
				vecCouple.clear();
				continue;
			}
			if(splitKeyValue(szLine, strKey, strValue))
			{				
				trim(strKey, strKey);
				trim(strValue, strValue);
				m_data[strSection].push_back(make_pair(strKey, strValue));
			}
		}
	}

	void CIniPro::trim( const std::string strSrc, __out std::string& strRes, const char cTrim /*= ' '*/ )
	{
		int nLen = strSrc.length();
		int nBegin = 0, nEnd = nLen;
		int nBreak;
		for (int i = 0; i < (nLen /2); i++)
		{
			nBreak = 0;
			if (strSrc.at(i) == cTrim)
			{
				nBegin = i + 1;
			}
			else
			{
				nBreak++;
			}
			if (strSrc.at(nLen - i - 1) == cTrim)
			{
				nEnd = nLen - i - 1;
			}
			else
			{
				nBreak++;
			}
			if (nBreak >= 2)
			{
				break;
			}
		}
		std::string _temp = strSrc.substr(0, nEnd);
		strRes = _temp.substr(nBegin, _temp.length() + 1 - nBegin);
	}	

	bool CIniPro::splitKeyValue( const std::string strSrc, __out std::string& strKey, __out std::string& strValue, const char cSplit /*= '='*/ )
	{
		const int nLen = strSrc.length();
		int nKeyPos = 0, nValuePos = 0;
		for (int i = 0; i < nLen; i++)
		{
			if (strSrc.at(i) == cSplit)
			{
				nKeyPos = i;
				strKey = strSrc.substr(0, nKeyPos);
				strValue = strSrc.substr(nKeyPos + 1);
				return true;
			}
		}
		return false;
	}
}
