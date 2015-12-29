// ZIniPro.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "IniPro_export.h"
#include "IniPro.h"

ZIniProExport Ini_Pro::iIniPro* CreateIniPro( const char* pFile , bool bCreateIfNotExist)
{
	Ini_Pro::CIniPro* ptr = new Ini_Pro::CIniPro;
	return ptr->Load(pFile, bCreateIfNotExist);
}

ZIniProExport void ReleaseIniPro( Ini_Pro::iIniPro* pPro )
{
	delete pPro;
}
