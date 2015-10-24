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

namespace ZoyeePro10
{
#define JSON_FILE				0
#define XML_FILE				1
	class IFileBase
	{
	public:
		char* ToString();
		int ToInt();
		bool ToBoolen();
	protected:
		char* m_pszValue;
	};
	
	class IFileNode : public IFileBase
	{
	public:
		//构造
		IFileNode(char* pszKey, char* pszValue);
		IFileNode(char* pszKey, int nValue);
		IFileNode(char* pszKey, bool bValue);
		IFileNode(char* pszKey, IFileNode* pNode);

		//序列化, 反序列化
		virtual char* FormatString() = 0;//序列化
		virtual IFileNode* Parse(char* pszString) = 0;//反序列化

		//取值, 填值
		virtual IFileNode* GetValue(char* pszKey) = 0;
		virtual void SetValue(char* pszKey, IFileNode* ptrNode) = 0;

		//取节点数量
		virtual int GetNodeSize() = 0;
		virtual int GetNodeSize(IFileNode* ptrNode) = 0;

		//遍历
		virtual IFileNode* First();
		virtual IFileNode* Next(IFileNode* pNode) = 0; 
		virtual IFileNode* Next() = 0;
		void* End();

		//查找
		virtual IFileNode* FindFirst(char* pszKey) = 0;
		virtual IFileNode* FindNext(char* pszKey) = 0;

	protected:
		IFileNode* pNode;
	};

	typedef IFileNode IFile;
	class ZFile CFileProtocol
	{
	public:
		IFile* Create(int nType = JSON_FILE);
		void Release(IFile* ptrFile);
	};
}

#endif