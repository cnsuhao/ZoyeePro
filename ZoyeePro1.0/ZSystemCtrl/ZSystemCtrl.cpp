// ZSystemCtrl.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ZSystemCtrl.h"


// ���ǵ���������һ��ʾ��
ZSYSTEMCTRL_API int nZSystemCtrl=0;

// ���ǵ���������һ��ʾ����
ZSYSTEMCTRL_API int fnZSystemCtrl(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� ZSystemCtrl.h
CZSystemCtrl::CZSystemCtrl()
{
	return;
}
