#pragma once
#include "zfile.h"
#include "json/json.h"

class CJsonPro : public ZoyeePro10::IFilePro
{
public:
	CJsonPro(void);
	virtual ~CJsonPro(void);

public:
	bool Parse(const char* pStrText);
	bool ParseFromFile(const char* pFileName);
	bool SaveToFile(const char* pFileName);
	const char* SaveToString();

private:
	Json::Reader m_JsonReader;
	Json::Value m_JsonRoot;
};

