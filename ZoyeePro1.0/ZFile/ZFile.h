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
	class IFileStream;
}

#endif