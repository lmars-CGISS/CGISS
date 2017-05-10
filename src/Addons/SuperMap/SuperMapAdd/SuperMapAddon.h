// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SUPERMAPADDON_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SUPERMAPADDON_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SUPERMAPADDON_EXPORTS
#define SUPERMAPADDON_API __declspec(dllexport)
#else
#define SUPERMAPADDON_API __declspec(dllimport)
#endif

#include "Addon.h"


/// \brief ����SuperMap UDB
extern "C" SUPERMAPADDON_API GIS::Addon*  ImportGPKGToUDB(void);

/// \brief ������SuperMap UDB�ļ�������
extern "C" SUPERMAPADDON_API GIS::Addon*  ExportGPKGFromUDB(void);

/// \brief ����GTIFF
extern "C" SUPERMAPADDON_API GIS::Addon*  ImportGTIFFToUDB(void);

/// \brief ������GTIFF
extern "C" SUPERMAPADDON_API GIS::Addon*  ExportGTIFFFromUDB(void);

