// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� GEOSTARADDON_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// GEOSTARADDON_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef GEOSTARADDON_EXPORTS
#define GEOSTARADDON_API __declspec(dllexport)
#else
#define GEOSTARADDON_API __declspec(dllimport)
#endif

#include "Addon.h" 

/// \brief ����GeoStar�ļ�������
extern "C" GEOSTARADDON_API GIS::Addon*  ImportGeoStarFCS(void);

/// \brief ������GeoStar�ļ�������
extern "C" GEOSTARADDON_API GIS::Addon*  ExportGeoStarFCS(void);
 

/// \brief ����GeoStar�ļ�������
extern "C" GEOSTARADDON_API GIS::Addon*  ImportGeoStarDOM(void);

/// \brief ������GeoStar�ļ�������
extern "C" GEOSTARADDON_API GIS::Addon*  ExportGeoStarDOM(void);

/// \brief ����GeoPackage��ʽ�ļ�
extern "C" GEOSTARADDON_API GIS::Addon*  ImportGPKG2GPKG(void);

/// \brief ����VCT��ʽ�ļ�
extern "C" GEOSTARADDON_API GIS::Addon*  ImportVCT2GPKG(void);

/// \brief ����VCT��ʽ�ļ�
extern "C" GEOSTARADDON_API GIS::Addon*  ExportGPKG2VCT(void);


