// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 GEOSTARADDON_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// GEOWAYADDON_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

#ifdef GEOWAYGDALDATAADDON_EXPORTS
#include <windows.h>
#define GEOWAYADDON_API __declspec(dllexport)
#else
#define GEOWAYADDON_API __declspec(dllimport)
#endif
#include "Addon.h" 
#include "gwStandardMetaDataAnalysis.h"
/// \brief 导入Geoway db文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ImportGeowayDB(void);

/// \brief 导出到Geoway db文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ExportGeowayDB(void);

/// \brief 导入AE mdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ImportMdb(void);

/// \brief 导出到AE mdb文件地物类
//extern "C" GEOWAYADDON_API GIS::Addon*  ExportMdb(void);

/// \brief 导入AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ImportFgdb(void);

/// \brief 导出到AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ExportFgdb(void);

/// \brief 导入AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ImportShp(void);

/// \brief 导出到AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ExportShp(void);
//
///// \brief 导入AE fgdb文件地物类
//extern "C" GEOWAYADDON_API GIS::Addon*  ImportIMG(void);
//
///// \brief 导出到AE fgdb文件地物类
//extern "C" GEOWAYADDON_API GIS::Addon*  ExportIMG(void);

/// \brief 导入AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ImportRaster(void);

/// \brief 导出到AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ExportRaster(void);

/// \brief 导出到AE fgdb文件地物类
extern "C" GEOWAYADDON_API GIS::Addon*  ImportMDBS(void);
extern "C" GEOWAYADDON_API GIS::Addon*  ImportGTIFFS(void);
extern "C" GEOWAYADDON_API GIS::Addon*  ImportIMGS(void);
extern "C" GEOWAYADDON_API GIS::Addon*  ImportGRIDS(void);
