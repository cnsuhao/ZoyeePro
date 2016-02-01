#ifndef __LOCK_MAN_H__
#define __LOCK_MAN_H__

#include <Windows.h>

namespace TOOLS
{
	class CLockMan
	{
	public:
		CLockMan(void);
		virtual ~CLockMan(void);
		CRITICAL_SECTION cs;
		class Locker
		{
		public:
			Locker(CLockMan& key);
			~Locker();
		private:
			CLockMan& m_key;
		};
	};

	inline CLockMan::CLockMan()
	{
		::InitializeCriticalSection(&cs);
	}

	inline CLockMan::~CLockMan()
	{
		::DeleteCriticalSection(&cs);
	}

	inline CLockMan::Locker::Locker(CLockMan& key) : m_key(key)
	{
		::EnterCriticalSection(&m_key.cs);
	}

	inline CLockMan::Locker::~Locker()
	{
		::LeaveCriticalSection(&m_key.cs);
	}
}

#define LOCK TOOLS::CLockMan::Locker
#define _LOCK_ TOOLS::CLockMan::Locker lock(key)
#define _KEY_ TOOLS::CLockMan key

#endif