#ifndef __SELECT_MODEL_H__
#define __SELECT_MODEL_H__

#include "BetterSelect.h"
#include <string>
#include <list>
#include <vector>
#include "Lockman.hpp"



namespace nsSelect
{	
	class CSocketArray
	{
	public:
		CSocketArray(void* pFdSet);
		~CSocketArray();
		bool AddSocket(unsigned int nSocket);
		bool RemoveSocket(unsigned int nSocket);
		int GetSize(){return nSize;};
		void SetSelect(void* pFdSet);
		void* GetFd(){return pFdSet;};
	protected:
		_KEY_;
		unsigned int arraySocket[MaxArraySize];
		int nSize;
		void* pFdSet;
	};
	

	class CSelectModel : public ISelectModel
	{
	public:
		CSelectModel(nsSelect::ICallback* pCallbackPtr);
		virtual int Send(const char* pBuff, const int nLen, unsigned int nSocket);
		virtual bool InitServer(const char* pHostIP, const int nPort);
		virtual void DisConnect(unsigned int nSocket);
		virtual int GetConnectCounts();
		virtual const char* GetLastError();

	protected:
		int PushToThread(unsigned int nSocket);
		void RemoveSocketArray(CSocketArray* pSocketArray);
		static DWORD WINAPI WorkThread(void* pParam);
		static DWORD WINAPI AcceptThread(void* pParam);

	protected:		
		std::list<CSocketArray*> lstSocketArray;
		void* hAccept;		

	protected:
		_KEY_;
		unsigned int sockServer;
		std::string strError;
	};
}



#endif