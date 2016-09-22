// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 GEOSTARADDON_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// GEOSTARADDON_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef GEOSTARADDON_EXPORTS
#define GEOSTARADDON_API __declspec(dllexport)
#else
#define GEOSTARADDON_API __declspec(dllimport)
#endif

#include "Addon.h" 

/// \brief 导入GeoStar文件地物类
extern "C" GEOSTARADDON_API GIS::Addon*  ImportGeoStarFCS(void);

/// \brief 导出到GeoStar文件地物类
extern "C" GEOSTARADDON_API GIS::Addon*  ExportGeoStarFCS(void);
 

/// \brief 导入GeoStar文件地物类
extern "C" GEOSTARADDON_API GIS::Addon*  ImportGeoStarDOM(void);

/// \brief 导出到GeoStar文件地物类
extern "C" GEOSTARADDON_API GIS::Addon*  ExportGeoStarDOM(void);

/// \brief 导入GeoPackage格式文件
extern "C" GEOSTARADDON_API GIS::Addon*  ImportGPKG2GPKG(void);

/// \brief 导入VCT格式文件
extern "C" GEOSTARADDON_API GIS::Addon*  ImportVCT2GPKG(void);

/// \brief 导出VCT格式文件
extern "C" GEOSTARADDON_API GIS::Addon*  ExportGPKG2VCT(void);


