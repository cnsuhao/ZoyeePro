// ZSystemCtrl.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZSystemCtrl.h"


ZoyeePro10::CSystemInfo::CSystemInfo()
{
	arrIP = NULL;
	pHostName = NULL;
	nIpCount = 0;
}

void ZoyeePro10::CSystemInfo::Release()
{
	delete this;
}

ZoyeePro10::CModule::CModule()
{
	pDirPath = NULL;
}

void ZoyeePro10::CModule::Release()
{
	delete this;
}

ZoyeePro10::CRegTools* ZoyeePro10::CRegTools::Instance()
{
	if (m_ptrInstance == NULL)
	{
		m_ptrInstance = new CRegTools;
	}
	return m_ptrInstance;
}

void ZoyeePro10::CRegTools::Release()
{
	if (m_ptrInstance)
	{
		delete m_ptrInstance;
		m_ptrInstance = NULL;
	}
}

bool ZoyeePro10::CRegTools::QueryValue( const char* pPath, const char* pKey, char* pValueOut )
{
	return false;
}

bool ZoyeePro10::CRegTools::WriteValue( const char* pPath, const char* pKey, char* pValue, int nType )
{
	return true;
}

ZoyeePro10::CRegTools* ZoyeePro10::CRegTools::m_ptrInstance = NULL;
