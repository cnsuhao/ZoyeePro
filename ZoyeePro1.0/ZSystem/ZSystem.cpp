// ZSystem.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZSystem.h"


ZSystem  bool ZoyeePro10::IsOS_X64()
{
	typedef void (WINAPI *pFnGetNativeSystemInfo)(SYSTEM_INFO* lpSystemInfo);
	SYSTEM_INFO si = { 0 };  
	pFnGetNativeSystemInfo pFun = (pFnGetNativeSystemInfo)GetProcAddress(GetModuleHandleA("kernel32.dll"), "GetNativeSystemInfo");  
	if (pFun != NULL)
	{
		pFun(&si);
	}
	else
	{
		GetSystemInfo(&si);
	}

	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
	{
		return true;
	}
	return false;
}

ZSystem  int ZoyeePro10::GetValueFromReg( char* lpSubKey, char* pRes, int nType /*= INT_TYPE*/, char* pHKEY /*= HKEY_CURRENT_USER*/ )
{
	HKEY hKey;
	if (strstr(pHKEY, "HKEY_CURRENT_USER") != NULL)
	{
		hKey = HKEY_CURRENT_USER;
	}
	else if (strstr(pHKEY, "HKEY_CLASSES_ROOT") != NULL)
	{
		hKey = HKEY_CLASSES_ROOT;
	}
	else if(strstr(pHKEY, "HKEY_LOCAL_MACHINE") != NULL)
	{
		hKey = HKEY_LOCAL_MACHINE;
	}
	else if(strstr(pHKEY, "HKEY_USERS") != NULL)
	{
		hKey = HKEY_USERS;
	}
	else if(strstr(pHKEY, "HKEY_CURRENT_CONFIG") != NULL)
	{
		hKey = HKEY_CURRENT_CONFIG;
	}
	else
	{
		return -1;
	}
	HKEY hSubKey = NULL;
	int nAppendX64Param = (IsOS_X64() ? KEY_WOW64_64KEY : 0);
	int n = 1u;
	if (ERROR_SUCCESS == RegOpenKeyExA(hKey, lpSubKey, 0, (KEY_READ | nAppendX64Param), &hSubKey))
	{
		if (hSubKey)
		{
			DWORD dwSize = 0, dwType = 0;
			if (nType == INT_TYPE)
			{
				DWORD dwValue;
				dwType = REG_DWORD;
				dwSize = sizeof(dwValue);
				if(RegQueryValueExA(hSubKey, "InstallDir", 0, &dwType, (LPBYTE)&dwValue, &dwSize) == ERROR_SUCCESS)
				{
					sprintf(pRes, "%d", dwValue);
					return 0;
				}
			}
			else
			{
				char szValue[1024] = {0};
				dwType = REG_SZ;
				dwSize = sizeof(szValue);
				if(RegQueryValueExA(hSubKey, "test", 0, &dwType, (LPBYTE)&szValue, &dwSize) == ERROR_SUCCESS)
				{
					strcpy(pRes, szValue);
					return 0;
				}
			}			
		}
	}
	return -1;
}

ZSystem int ZoyeePro10::CmdOutputByPipe( char* cmd, char* res )
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;  
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL;  //使用系统默认的安全描述符 
	sa.bInheritHandle = TRUE;  //创建的进程继承句柄
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))  //创建匿名管道
	{  
		strcpy(res, "create pipe fail!");
		return -1;
	}

	STARTUPINFO si; 
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si); 
	GetStartupInfo(&si); 	
	si.hStdOutput = hWrite;  //新创建进程的标准输出连在写管道一端
	si.wShowWindow = SW_HIDE;  //隐藏窗口 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	TCHAR sz[1024] = {0};
	MultiByteToWideChar(CP_ACP, 0, cmd, -1, sz, 1024);  

	if (!CreateProcess(NULL, sz, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))  //创建子进程
	{
		strcpy(res, "createprocess fail!");
		return false;
	}

	CloseHandle(hWrite);  //关闭管道句柄
	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD bytesRead;
	memset(res, 0, 1024);
	while (true) 
	{
		if (ReadFile(hRead, res, 1024, &bytesRead, NULL) == NULL)  //读取管道
		{
			break;
		}
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hRead);
	return 0;
}

ZoyeePro10::CHardwareInfo::CHardwareInfo() : 
	m_pCpuInfo(nullptr), 
	m_pHdInfo(nullptr),
	m_nCpuCount(0),
	m_nHDCount(0)
{

}

ZoyeePro10::CHardwareInfo::~CHardwareInfo()
{
	if (nullptr != m_pCpuInfo)
	{
		delete[] m_pCpuInfo;
		m_pCpuInfo = nullptr;
	}
	if (nullptr != m_pHdInfo)
	{
		delete[] m_pHdInfo;
		m_pHdInfo = nullptr;
	}
}
