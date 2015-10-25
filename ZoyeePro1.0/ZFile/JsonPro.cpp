#include "stdafx.h"
#include "JsonPro.h"


CJsonPro::CJsonPro(void)
{
}


CJsonPro::~CJsonPro(void)
{
}

bool CJsonPro::Parse( const char* pStrText )
{
	return m_JsonReader.parse(pStrText, m_JsonRoot);	
}

bool CJsonPro::ParseFromFile( const char* pFileName )
{
	ifstream file(pFileName);
	return m_JsonReader.parse(file, m_JsonRoot);
}

bool CJsonPro::SaveToFile( const char* pFileName )
{
	ofstream out;
	out.open(pFileName, ios::out);
	const char* pJson = m_JsonRoot.toStyledString().c_str();
	if (pJson)
	{
		out << pJson;
		return true;
	}
	return false;
}

const char* CJsonPro::SaveToString()
{
	return m_JsonRoot.toStyledString().c_str();
}
