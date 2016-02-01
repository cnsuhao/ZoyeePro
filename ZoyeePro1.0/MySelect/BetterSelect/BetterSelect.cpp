// BetterSelect.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "BetterSelect.h"
#include "SelectModel.h"

extern "C" SELECT_EX_EXPORT void ReleaseSelectModel( nsSelect::ISelectModel* pModel )
{

}

extern "C" SELECT_EX_EXPORT nsSelect::ISelectModel* CreateSelectModel( nsSelect::ICallback* pCallbackPtr, const char* pHostIP, const int nPort )
{
	nsSelect::CSelectModel* pSelect = new nsSelect::CSelectModel(pCallbackPtr);
	if(pSelect->InitServer(pHostIP, nPort) != true)
	{
		delete pSelect;
		pSelect = NULL;
	}
	return pSelect;
}

nsSelect::ISelectModel::ISelectModel( nsSelect::ICallback* pCallbackPtr )
{
	this->m_pCallbackPtr = pCallbackPtr;
}
