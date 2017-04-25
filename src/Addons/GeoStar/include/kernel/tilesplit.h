#pragma once
#include "../utility/preconfig.h"
#include "utility.h"  
#include "geodatabase.h"

KERNEL_NS

/// \brief GsFileVectorTileSpliter
/// \detail 文件式瓦片切割类
class GS_API GsFileVectorTileSpliter:public Utility::GsRefObject
{  
	struct LayerStruct:public GsVector<Utility::GsString>
	{
		int Index;
		Utility::GsString Name;
		LayerStruct()
		{
			Index = 0;
		}
		LayerStruct(int index,const char* name)
		{
			Index = index;
			Name = name;
		}
	};
	/// \brief 金字塔对象
	GsPyramidPtr		m_ptrPyramid;
	/// \brief 切片级别范围
	int m_MinLevel,m_MaxLevel;
	/// \brief 总碎片数
	long long m_nTotalPieces;
	/// \brief 几何简化容差
	double m_SimplfyTol;
	/// \brief 瓦片数据集对象
	GsTileClassPtr				m_ptrTileClass;
	/// \brief 坐标转换对象
	GsCoordinateTransformationPtr m_ptrTans;
	/// \brief 切片过滤范围
	geostar::gobjptr			m_FilterExtent;
	/// \brief 瓦片属性缓存
	Utility::GsGrowByteBuffer m_AttributeBuffer;
	/// \brief 瓦片图层索引缓存
	std::map<std::string,LayerStruct> m_LayerIndex;
	/// \brief 切片对象缓存
	std::map<int,geostar::gobjptr> m_ClipCache;
	/// \brief 临时切片文件io对象
	geostar::geo_reader2* m_TempRW;
	// 切片临时文件存储路径
	Utility::GsString m_strCacheFile;

	/// \brief 创建临时切片文件io对象
	void CreateReader();
	/// \brief 获取图层的索引
	int LayerIndex(const char* layerName,GsFeature* pFea,int* pAttIndex,int nAttCount);
	/// brief 根据level创建一个clip
	geostar::geo_trans* CreateClip(int nLevel);
	/// brief 写一个碎片到临时文件
	void Write(geostar::geo_object* o);
public:
	GsFileVectorTileSpliter(GsTileClass* pTileClass,GsPyramid* pPyramid,int nMin,int nMax,double dblSimplfyTol = 0);
	virtual ~GsFileVectorTileSpliter();
	
	/// \brief 设置过滤范围,过滤范围外的数据不会进入瓦片
	void FilterExtent(GsBox& box);
	/// \brief 设置过滤范围，过滤范围外的数据不会进入瓦片
	void FilterExtent(GsGeometry* pGeo);

	/// \brief 坐标转换对象
	void CoordinateTransformation(GsCoordinateTransformation* ptrTransObj);
	/// \brief 坐标转换对象 
	GsCoordinateTransformation* CoordinateTransformation();
	/// \brief 设置获取最小的切片级别
	int& MinLevel();
	/// \brief 设置获取最大的切片级别
	int& MaxLevel();
	/// \brief 添加一个Feature进行瓦片切割。
	bool Add(GsFeature* pFea,int* pAttIndex,int nAttCount,const char* lyrName =  NULL);
	/// \brief 提交数据。
	virtual void Commit(); 

	/// \brief 设置GZip压缩是否有效
	void GZipCompress(bool bEnable);

	/// \brief 设置切片临时文件存储路径
	void CachePath(const char* strPath);

public:
	/// \brief 当提交数据时显示进度。
	Utility::GsDelegate<void(long long,long long)> OnCommit;
};

/// \brief GsFileVectorTileSpliterPtr
GS_SMARTER_PTR(GsFileVectorTileSpliter);

KERNEL_ENDNS