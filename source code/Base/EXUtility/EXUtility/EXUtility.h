// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� EXUTILITY_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// EXUTILITY_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef EXUTILITY_EXPORTS
#define EXUTILITY_API __declspec(dllexport)
#else
#define EXUTILITY_API __declspec(dllimport)
#endif

// �����Ǵ� EXUtility.dll ������
class EXUTILITY_API CEXUtility {
public:
	CEXUtility(void);
	// TODO: �ڴ�������ķ�����
};

extern EXUTILITY_API int nEXUtility;

EXUTILITY_API int fnEXUtility(void);
