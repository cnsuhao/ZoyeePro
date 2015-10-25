#pragma once
#include "zfile.h"
#include "tinyxml2/tinyxml2.h"

class CXmlPro :	public ZoyeePro10::IFilePro
{
public:
	CXmlPro(void);
	virtual ~CXmlPro(void);

	bool Parse(const char* pStrText);
	bool ParseFromFile(const char* pFileName);
	bool SaveToFile(const char* pFileName);
	const char* SaveToString();

private:
	tinyxml2::XMLDocument doc;
};

