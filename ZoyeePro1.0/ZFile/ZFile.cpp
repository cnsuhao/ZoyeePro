// ZFile.cpp : ���� DLL Ӧ�ó���ĵ���������
//
//--------------------------------------
//  �ļ�·���� D:\Zoyee\ZoyeePro\ZoyeePro1.0\ZFile\ZFile.cpp
//  �ļ����ܣ�
//
//  ����ʱ�䣺 2015-10-24 9:42:52
//  author:		Zoyee
//  �޸�ʱ��
//
#include "stdafx.h"
#include "ZFile.h"

using namespace ZoyeePro10;

char* ZoyeePro10::IFileBase::ToString()
{
	return m_pszValue;
}

int ZoyeePro10::IFileBase::ToInt()
{
	return atoi(m_pszValue);
}

bool ZoyeePro10::IFileBase::ToBoolen()
{
	if ((m_pszValue[0] == 't' || m_pszValue[0] == 'T') && 
		(m_pszValue[1] == 'r' || m_pszValue[1] == 'R') &&
		(m_pszValue[2] == 'u' || m_pszValue[2] == 'U') &&
		(m_pszValue[3] == 'e' || m_pszValue[3] == 'E'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

IFileNode* ZoyeePro10::CFileProtocol::Create( int nType /*= JSON_FILE*/ )
{
	return nullptr;
}
