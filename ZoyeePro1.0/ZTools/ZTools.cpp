// ZTools.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZTools.h"
#include "IKeyCore.h"
#include "KeyCriSection.h"
#include "KeyReadWrite.h"
#include <assert.h>

ZoyeePro10::IKeyManage::IKeyManage(emKeyType nType) :
	pKeyCore(nullptr), 
	nKeyType(nType)
{
	switch(nType)
	{
	case AutoCriSetion:
	case ManualCriSetion:
		pKeyCore = new CKeyCriSection;
		break;
	case RWLock:
		pKeyCore = new CKeyReadWrite;
		break;
	default:
		break;
	}
	assert(pKeyCore);
}

ZoyeePro10::IKeyManage::~IKeyManage()
{
	assert(pKeyCore);
	delete pKeyCore;
	pKeyCore = nullptr;
}

void ZoyeePro10::IKeyManage::Lock(bool bIsReadLock /*= false*/) const
{
	assert(pKeyCore);
	pKeyCore->Lock(bIsReadLock);
}


void ZoyeePro10::IKeyManage::UnLock(bool bIsReadLock /*= false*/) const
{
	assert(pKeyCore);
	pKeyCore->UnLock(bIsReadLock);
}

ZoyeePro10::ILock::ILock( IKeyManage& keyMgr ):
	m_keyMgr(keyMgr)
{
	if (m_keyMgr.nKeyType == AutoCriSetion)
	{
		m_keyMgr.Lock();
	}
}

ZoyeePro10::ILock::~ILock()
{
	if (m_keyMgr.nKeyType == AutoCriSetion)
	{
		m_keyMgr.UnLock();
	}
}

void ZoyeePro10::ILock::Lock( bool bIsReadLock /*= false*/)
{
	m_keyMgr.Lock(bIsReadLock);
}

void ZoyeePro10::ILock::UnLock( bool bIsReadLock /*= false*/ )
{
	m_keyMgr.UnLock(bIsReadLock);
}
