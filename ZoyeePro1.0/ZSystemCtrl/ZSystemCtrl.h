// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZSYSTEMCTRL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZSYSTEMCTRL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZSYSTEMCTRL_EXPORTS
#define ZSYSTEMCTRL_API __declspec(dllexport)
#else
#define ZSYSTEMCTRL_API __declspec(dllimport)
#endif

// �����Ǵ� ZSystemCtrl.dll ������
class ZSYSTEMCTRL_API CZSystemCtrl {
public:
	CZSystemCtrl(void);
	// TODO: �ڴ�������ķ�����
};

extern ZSYSTEMCTRL_API int nZSystemCtrl;

ZSYSTEMCTRL_API int fnZSystemCtrl(void);
