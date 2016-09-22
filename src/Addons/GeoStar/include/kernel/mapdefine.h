#pragma once
#include "../utility/preconfig.h"
#include "map.h" 
KERNEL_NS  
	
/// \brief 地图定义文件读写类
class GS_API GsMapDefine
{
	/// \brief 地图定义文件的文件路径
	Utility::GsString m_strFile;
public:
	GsMapDefine();

	/// \brief 从地图定义文件打开
	GsMapDefine(const char* strFilePath);
	
	/// \brief 设置地图定义文件的路径
	void FilePath(const char* strFilePath);
	
	/// \brief 获取地图定义文件的路径
	Utility::GsString FilePath();

	/// \brief 解析地图定义文件为地图
	bool ParserMap(GsMap* pMap);

	/// \brief 解析地图定义文件为地图
	bool ParserMap(const char* strFilePath,GsMap* pMap);

	/// \brief 解析地图定义文件为地图
	bool ParserMap(const char* strGmdXML,const char* strSymXML,GsMap* pMap);

	/// \brief 保存到文件
	bool SaveMap(GsMap* pMap, const char* strFilePath);

};

KERNEL_ENDNS