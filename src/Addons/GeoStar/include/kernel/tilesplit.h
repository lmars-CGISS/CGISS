#pragma once
#include "../utility/preconfig.h"
#include <utility.h>  
#include "geodatabase.h"
#include "geometry.h"  
#include "pyramid.h" 
#include "spatialreference.h"
#include <list>
#include <map>
#include <GeomathSE.inl>
#include <gobject.inl>

class GsVecTileCache;

KERNEL_NS    
/// \brief 瓦片切割基类
class GS_API GsVectorTileSpliter:public Utility::GsRefObject
{
	geostar::geo_factory* m_pFac;
	int m_nMaxTileCount;
	GsPyramidPtr m_ptrPyramid;
	GsCoordinateTransformationPtr m_ptrTransObj;
	int m_nMinLevel,m_nMaxLevel;
	double m_dblSimplfyTol;
	
	/// \brief 做简化用的转换类
	std::map<int,geostar::gobjptr> m_mapSimplfy;
	
	/// \brief geometry切割的转换类
	std::map<int,geostar::gobjptr> m_mapSplit;

	geostar::gobjptr m_ObjGeoCut;

	geostar::gobjptr SimplfyObject(int l);
	geostar::gobjptr SplitObject(int l);

	void Add(geostar::gobjptr &ptrSimplfy,geostar::gobjptr &ptrSplit,GsFeature* pFea,geostar::gobjptr &ptrGeo,int l,
		const std::vector<std::pair<std::string,GeoStar::Utility::GsAny> >& vecAtt,const char* lyrName);
protected:
	// 瓦片缓存
	UTILITY_NAME::GsSmarterPtr<GsVecTileCache> m_pTileCache;
protected:
	/// \brief 获取一个瓦片对象
	virtual GsTile* GetTile(int l,int r,int c);
	
	/// \brief 从存储介质读取一个瓦片的内容。
	virtual bool ReadTile(GsTile* pTile) = 0; 
	/// \brief 存储瓦片到介质
	virtual bool SaveTile(GsTile* pTile) = 0; 

public:
	GsVectorTileSpliter(GsPyramid* pPyramid,int nMin,int nMax,double dTileCacheSize=1.5,double dblSimplfyTol=0.00390625);
	virtual ~GsVectorTileSpliter();
	/// \brief 
	void SetCoordinateTransObj(GsCoordinateTransformation* ptrTransObj);
	/// \brief 
	GsCoordinateTransformation* GetCoordinateTransObj();
	/// \brief 设置获取最小的切片级别
	int& MinLevel();
	/// \brief 设置获取最大的切片级别
	int& MaxLevel();

	/// \brief 添加一个Feature进行瓦片切割。
	void Add(GsFeature* pFea,int* pAttIndex,int nAttCount,const char* lyrName =  NULL);
	///// \brief 设置获取最大瓦片数量
	//int& MaxTileCount();

	/// \brief 关闭。
	virtual void Close();

	void SetBlockBox(const GsBox& box);
	GsBox GetBlockBox(){ return m_BlockBox; }

private:
	void GetAttFields(GsFeature *pFea, int* pAttIndex,int nAttCount, std::vector<std::pair<std::string,GeoStar::Utility::GsAny> >& vecAtt);
	void CutGeometry(int nLevel, const GsBox& boxGeo, geostar::gobjptr& ptrGeo);

private:
	GsBox m_BlockBox;
};
// 瓦片地物类。
class GS_API GsTileClassVTSpiter:public GsVectorTileSpliter
{
	GsTileClassPtr m_ptrTileClass;
	GsTilePtr		m_ptrTile;
	int				m_nCommitCount;
protected:
	/// \brief 从存储介质读取一个瓦片的内容。
	virtual bool ReadTile(GsTile* pTile); 
	
	/// \brief 存储瓦片到介质
	virtual bool SaveTile(GsTile* pTile); 
public:
	GsTileClassVTSpiter(GsTileClass* pTileClass,GsPyramid* pPyramid,int nMin,int nMax,double dTileCacheSize=1.5,double dblSimplfyTol=0.00390625);
	virtual ~GsTileClassVTSpiter();
	/// \brief 关闭。
	virtual void Close();
};



/// \brief 瓦片切割基类
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
	GsPyramidPtr		m_ptrPyramid;
	int m_MinLevel,m_MaxLevel;
	long long m_nTotalPieces;
	double m_SimplfyTol;
	GsTileClassPtr				m_ptrTileClass;
	GsCoordinateTransformationPtr m_ptrTans;
	//过滤范围。
	geostar::gobjptr			m_FilterExtent;

	Utility::GsGrowByteBuffer m_AttributeBuffer;
	std::map<std::string,LayerStruct> m_LayerIndex;
	std::map<int,geostar::gobjptr> m_ClipCache;
	geostar::geo_reader2* m_TempRW;
	
	int LayerIndex(const char* layerName,GsFeature* pFea,int* pAttIndex,int nAttCount);
	//根据level创建一个clip
	geostar::geo_trans* CreateClip(int nLevel);
	//写一个到临时文件
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

public:
	/// \brief 当提交数据时显示进度。
	Utility::GsDelegate<void(long long,long long)> OnCommit;
};

/// \brief GsFileVectorTileSpliterPtr
GS_SMARTER_PTR(GsFileVectorTileSpliter);

KERNEL_ENDNS