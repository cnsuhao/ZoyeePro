// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZFILE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZFILE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
//--------------------------------------
//  �ļ�·���� D:\Zoyee\ZoyeePro\ZoyeePro1.0\ZFile\ZFile.h
//  �ļ����ܣ�
//
//  ����ʱ�䣺 2015-10-24 9:43:05
//  author:		Zoyee
//  �޸�ʱ��
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
		//����
		IFileNode(char* pszKey, char* pszValue);
		IFileNode(char* pszKey, int nValue);
		IFileNode(char* pszKey, bool bValue);
		IFileNode(char* pszKey, IFileNode* pNode);

		//���л�, �����л�
		virtual char* FormatString() = 0;//���л�
		virtual IFileNode* Parse(char* pszString) = 0;//�����л�

		//ȡֵ, ��ֵ
		virtual IFileNode* GetValue(char* pszKey) = 0;
		virtual void SetValue(char* pszKey, IFileNode* ptrNode) = 0;

		//ȡ�ڵ�����
		virtual int GetNodeSize() = 0;
		virtual int GetNodeSize(IFileNode* ptrNode) = 0;

		//����
		virtual IFileNode* First();
		virtual IFileNode* Next(IFileNode* pNode) = 0; 
		virtual IFileNode* Next() = 0;
		void* End();

		//����
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