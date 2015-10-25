#include "stdafx.h"
#include "XmlPro.h"
#define FileName "{B5A50040-2FFD-44B8-8C4B-0662CEBEBE06}"

CXmlPro::CXmlPro(void)
{
}


CXmlPro::~CXmlPro(void)
{
}

bool CXmlPro::Parse( const char* pStrText )
{
	ofstream out(FileName);
	out << pStrText;
	out.flush();
	out.close();
	return ParseFromFile(FileName);
}


bool CXmlPro::ParseFromFile( const char* pFileName )
{
	return doc.LoadFile(pFileName);
}

bool CXmlPro::SaveToFile( const char* pFileName )
{
	return doc.SaveFile(pFileName);
}

const char* CXmlPro::SaveToString()
{
	doc.SaveFile(FileName);
	ifstream iFile(FileName);
	char sz[1024] = {0};
	int nCount = 0;
	string str;
	while( ! iFile.eof())
	{
		iFile.read(sz, 1024 - 1);
		nCount = iFile.gcount();
		if (nCount < (1024 - 1))
		{
			sz[nCount] = 0;
		}
		str += sz;
	}
	return str.c_str();
}
