// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZUTILS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZUTILS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZUTILS_EXPORTS
#define ZUTILS_API __declspec(dllexport)
#else
#define ZUTILS_API __declspec(dllimport)
#endif

// �����Ǵ� ZUtils.dll ������
class ZUTILS_API CZUtils {
public:
	CZUtils(void);
	// TODO: �ڴ�������ķ�����
};

extern ZUTILS_API int nZUtils;

ZUTILS_API int fnZUtils(void);
