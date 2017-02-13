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
/// \brief ��Ƭ�и����
class GS_API GsVectorTileSpliter:public Utility::GsRefObject
{
	geostar::geo_factory* m_pFac;
	int m_nMaxTileCount;
	GsPyramidPtr m_ptrPyramid;
	GsCoordinateTransformationPtr m_ptrTransObj;
	int m_nMinLevel,m_nMaxLevel;
	double m_dblSimplfyTol;
	
	/// \brief �����õ�ת����
	std::map<int,geostar::gobjptr> m_mapSimplfy;
	
	/// \brief geometry�и��ת����
	std::map<int,geostar::gobjptr> m_mapSplit;

	geostar::gobjptr m_ObjGeoCut;

	geostar::gobjptr SimplfyObject(int l);
	geostar::gobjptr SplitObject(int l);

	void Add(geostar::gobjptr &ptrSimplfy,geostar::gobjptr &ptrSplit,GsFeature* pFea,geostar::gobjptr &ptrGeo,int l,
		const std::vector<std::pair<std::string,GeoStar::Utility::GsAny> >& vecAtt,const char* lyrName);
protected:
	// ��Ƭ����
	UTILITY_NAME::GsSmarterPtr<GsVecTileCache> m_pTileCache;
protected:
	/// \brief ��ȡһ����Ƭ����
	virtual GsTile* GetTile(int l,int r,int c);
	
	/// \brief �Ӵ洢���ʶ�ȡһ����Ƭ�����ݡ�
	virtual bool ReadTile(GsTile* pTile) = 0; 
	/// \brief �洢��Ƭ������
	virtual bool SaveTile(GsTile* pTile) = 0; 

public:
	GsVectorTileSpliter(GsPyramid* pPyramid,int nMin,int nMax,double dTileCacheSize=1.5,double dblSimplfyTol=0.00390625);
	virtual ~GsVectorTileSpliter();
	/// \brief 
	void SetCoordinateTransObj(GsCoordinateTransformation* ptrTransObj);
	/// \brief 
	GsCoordinateTransformation* GetCoordinateTransObj();
	/// \brief ���û�ȡ��С����Ƭ����
	int& MinLevel();
	/// \brief ���û�ȡ������Ƭ����
	int& MaxLevel();

	/// \brief ���һ��Feature������Ƭ�и
	void Add(GsFeature* pFea,int* pAttIndex,int nAttCount,const char* lyrName =  NULL);
	///// \brief ���û�ȡ�����Ƭ����
	//int& MaxTileCount();

	/// \brief �رա�
	virtual void Close();

	void SetBlockBox(const GsBox& box);
	GsBox GetBlockBox(){ return m_BlockBox; }

private:
	void GetAttFields(GsFeature *pFea, int* pAttIndex,int nAttCount, std::vector<std::pair<std::string,GeoStar::Utility::GsAny> >& vecAtt);
	void CutGeometry(int nLevel, const GsBox& boxGeo, geostar::gobjptr& ptrGeo);

private:
	GsBox m_BlockBox;
};
// ��Ƭ�����ࡣ
class GS_API GsTileClassVTSpiter:public GsVectorTileSpliter
{
	GsTileClassPtr m_ptrTileClass;
	GsTilePtr		m_ptrTile;
	int				m_nCommitCount;
protected:
	/// \brief �Ӵ洢���ʶ�ȡһ����Ƭ�����ݡ�
	virtual bool ReadTile(GsTile* pTile); 
	
	/// \brief �洢��Ƭ������
	virtual bool SaveTile(GsTile* pTile); 
public:
	GsTileClassVTSpiter(GsTileClass* pTileClass,GsPyramid* pPyramid,int nMin,int nMax,double dTileCacheSize=1.5,double dblSimplfyTol=0.00390625);
	virtual ~GsTileClassVTSpiter();
	/// \brief �رա�
	virtual void Close();
};



/// \brief ��Ƭ�и����
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
	//���˷�Χ��
	geostar::gobjptr			m_FilterExtent;

	Utility::GsGrowByteBuffer m_AttributeBuffer;
	std::map<std::string,LayerStruct> m_LayerIndex;
	std::map<int,geostar::gobjptr> m_ClipCache;
	geostar::geo_reader2* m_TempRW;
	
	int LayerIndex(const char* layerName,GsFeature* pFea,int* pAttIndex,int nAttCount);
	//����level����һ��clip
	geostar::geo_trans* CreateClip(int nLevel);
	//дһ������ʱ�ļ�
	void Write(geostar::geo_object* o);
public:
	GsFileVectorTileSpliter(GsTileClass* pTileClass,GsPyramid* pPyramid,int nMin,int nMax,double dblSimplfyTol = 0);
	virtual ~GsFileVectorTileSpliter();
	
	/// \brief ���ù��˷�Χ,���˷�Χ������ݲ��������Ƭ
	void FilterExtent(GsBox& box);
	/// \brief ���ù��˷�Χ�����˷�Χ������ݲ��������Ƭ
	void FilterExtent(GsGeometry* pGeo);

	/// \brief ����ת������
	void CoordinateTransformation(GsCoordinateTransformation* ptrTransObj);
	/// \brief ����ת������ 
	GsCoordinateTransformation* CoordinateTransformation();
	/// \brief ���û�ȡ��С����Ƭ����
	int& MinLevel();
	/// \brief ���û�ȡ������Ƭ����
	int& MaxLevel();
	/// \brief ���һ��Feature������Ƭ�и
	bool Add(GsFeature* pFea,int* pAttIndex,int nAttCount,const char* lyrName =  NULL);
	/// \brief �ύ���ݡ�
	virtual void Commit(); 

public:
	/// \brief ���ύ����ʱ��ʾ���ȡ�
	Utility::GsDelegate<void(long long,long long)> OnCommit;
};

/// \brief GsFileVectorTileSpliterPtr
GS_SMARTER_PTR(GsFileVectorTileSpliter);

KERNEL_ENDNS