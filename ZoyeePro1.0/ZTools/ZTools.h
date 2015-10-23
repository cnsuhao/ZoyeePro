// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ZTOOLS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ZTOOLS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ZTOOLS_EXPORTS
#define ZTOOLS_API __declspec(dllexport)
#else
#define ZTOOLS_API __declspec(dllimport)
#endif

#define ZTools ZTOOLS_API

namespace ZoyeePro10
{
	class ZTools IKeyManage
	{

	};

	class ZTools ILock
	{
	public:
		ILock(IKeyManage& keyMgr);
		~ILock();
	private:
		const IKeyManage& m_keyMgr;
	};
}