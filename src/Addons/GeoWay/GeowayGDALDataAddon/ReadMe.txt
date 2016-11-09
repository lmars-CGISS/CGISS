/*!
* Copyright (c) 2010,北京吉威数源信息技术有限公司.
* All Rights Reserved.
* http://www.geoway.com.cn
*
* \libname gwProvider   
* \brief   项目概述
*
* \author  王少帅
* \date    2016/01/09
*/
====================================================
总体说明：
gwDataAddon动态库提供支持ISO19163标准的矢量数据与栅格数据的转换；
矢量数据主要支持GPKG、mdb、gdb、db文件；栅格数据主要支持GeoTIff、
GRID与IMG。
====================================================
接口文件说明：
1、	Addon								数据转换接口
2、	Progress							数据转换信息接口
3、	gwExportData						矢量数据转换geopackage接口
4、	gwImportData						geopackage转换矢量数据接口
5、	gwImportRaster						栅格数据转Geotiff接口
6、	gwExportRaster						GeoTiff转栅格数据接口
7、	gwTransform							提供的对外转换接口	
8、	OperationProgress					数据转换的信息接口

====================================================
依赖关系说明：

1、gwRaster			用于栅格数据转换
2、gwSystem			核心库
3、gwSystemDraft	提供一些公共数据模型
4、gwDataBase		用于矢量数据转换
5、xml-xerces库     用于XML文件读写

====================================================
资源文件说明：

		
====================================================
维护记录：
2015.11		王少帅	添加矢量数据转换接口
2016.01		王少帅	添加栅格数据转换接口

====================================================
其它：

