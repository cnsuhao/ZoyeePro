// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZFILE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZFILE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
//--------------------------------------
//  文件路径： D:\Zoyee\ZoyeePro\ZoyeePro1.0\ZFile\ZFile.h
//  文件功能：
//
//  创建时间： 2015-10-24 9:43:05
//  author:		Zoyee
//  修改时间
//
#ifdef ZFILE_EXPORTS
#define ZFILE_API __declspec(dllexport)
#else
#define ZFILE_API __declspec(dllimport)
#endif

#ifndef __ZFILE_H__
#define __ZFILE_H__
#define ZFile ZFILE_API

#include <fstream>
using namespace std;

namespace ZoyeePro10
{
#define JSON_FILE				0
#define XML_FILE				1
	class IValue;
	class IRoot;
	class IFilePro
	{
	public:
		//初始化与结束
		virtual bool Parse(const char* pStrText) = 0;
		virtual bool ParseFromFile(const char* pFileName) = 0;
		virtual bool SaveToFile(const char* pFileName) = 0;
		virtual const char* SaveToString() = 0;
	};

	class ZFile CFilePro
	{
	public:
		IFilePro* Create(int nProtocolType = JSON_FILE);
		//IFilePro(const char* pFileText, int nProtocolType = JSON_FILE);//由于无法感知错误, 还是放弃使用


	protected:
		void* pCore;
	};
}

#endif