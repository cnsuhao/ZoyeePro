// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZNETWORK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZNETWORK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZNETWORK_EXPORTS
#define ZNETWORK_API __declspec(dllexport)
#else
#define ZNETWORK_API __declspec(dllimport)
#endif

// �����Ǵ� ZNetwork.dll ������
class ZNETWORK_API CZNetwork {
public:
	CZNetwork(void);
	// TODO: �ڴ�������ķ�����
};

extern ZNETWORK_API int nZNetwork;

ZNETWORK_API int fnZNetwork(void);
