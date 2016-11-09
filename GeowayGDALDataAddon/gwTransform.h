// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� GEOSTARADDON_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// GEOWAYADDON_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifdef GEOWAYGDALDATAADDON_EXPORTS
#include <windows.h>
#define GEOWAYADDON_API __declspec(dllexport)
#else
#define GEOWAYADDON_API __declspec(dllimport)
#endif
#include "Addon.h" 
#include "gwStandardMetaDataAnalysis.h"
/// \brief ����Geoway db�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ImportGeowayDB(void);

/// \brief ������Geoway db�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ExportGeowayDB(void);

/// \brief ����AE mdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ImportMdb(void);

/// \brief ������AE mdb�ļ�������
//extern "C" GEOWAYADDON_API GIS::Addon*  ExportMdb(void);

/// \brief ����AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ImportFgdb(void);

/// \brief ������AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ExportFgdb(void);

/// \brief ����AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ImportShp(void);

/// \brief ������AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ExportShp(void);
//
///// \brief ����AE fgdb�ļ�������
//extern "C" GEOWAYADDON_API GIS::Addon*  ImportIMG(void);
//
///// \brief ������AE fgdb�ļ�������
//extern "C" GEOWAYADDON_API GIS::Addon*  ExportIMG(void);

/// \brief ����AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ImportRaster(void);

/// \brief ������AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ExportRaster(void);

/// \brief ������AE fgdb�ļ�������
extern "C" GEOWAYADDON_API GIS::Addon*  ImportMDBS(void);
extern "C" GEOWAYADDON_API GIS::Addon*  ImportGTIFFS(void);
extern "C" GEOWAYADDON_API GIS::Addon*  ImportIMGS(void);
extern "C" GEOWAYADDON_API GIS::Addon*  ImportGRIDS(void);
