// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZSYSTEM_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZSYSTEM_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZSYSTEM_EXPORTS
#define ZSYSTEM_API __declspec(dllexport)
#else
#define ZSYSTEM_API __declspec(dllimport)
#endif

// �����Ǵ� ZSystem.dll ������
class ZSYSTEM_API CZSystem {
public:
	CZSystem(void);
	// TODO: �ڴ�������ķ�����
};

extern ZSYSTEM_API int nZSystem;

ZSYSTEM_API int fnZSystem(void);
