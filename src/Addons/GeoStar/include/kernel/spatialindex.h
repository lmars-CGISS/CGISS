#pragma once
#include "../utility/preconfig.h"
#include <utility.h>  
#include <geometry.h>
#include <map>
KERNEL_NS 

	
/// \brief 粗查空间索引对象抽象基类
class GS_API GsSpatialIndexQuery:public Utility::GsRefObject
{
public:
	virtual ~GsSpatialIndexQuery();
	/// \brief 根据矩形范围查询相交对象id
	/// \param box 要检索的矩形范围
	/// \param vecResult 返回和检索矩形相交的对象id
	/// \return 返回是否检索到对象
	virtual bool Query(const GsBox& box,GsVector<int> &vecResult) = 0;
};
/// \brief GsSpatialIndexQueryPtr
GS_SMARTER_PTR(GsSpatialIndexQuery);

/// \brief 支持修改的空间索引抽象基类
class GS_API GsSpatialIndexEdit:public GsSpatialIndexQuery
{
public:
	virtual ~GsSpatialIndexEdit();
	/// \brief 增加一个对象到空间索引
	/// \param box 要增加对象的box
	/// \param nID 要增加对象的id
	/// \return 增加是否成功
	virtual bool Add(const GsBox& box,int nID) = 0;
	/// \brief 从空间索引移除一个对象
	/// \param nID 要移除对象的id
	/// \return 移除是否成功
	virtual bool Remove(int nID) = 0;
};
/// \brief GsSpatialIndexEditPtr
GS_SMARTER_PTR(GsSpatialIndexEdit);


/// \brief 在内存中的R树索引实现
class GS_API GsMemoryRTreeSpatialIndex:public GsSpatialIndexEdit
{
	void* m_pTree;
	std::map<int,void*> m_Object;
public:
	virtual ~GsMemoryRTreeSpatialIndex();

	/// \brief 根据R树索引深度和维度构造
	/// \param nMaxDepth 最大的R树深度，范围[3~8]
	/// \param nDim 索引坐标的维[2,4]
	GsMemoryRTreeSpatialIndex(const double* minBound,const double* maxBound,int nMaxDepth =  8,int nDim =  2);

	/// \brief R树最大深度
	int MaxDepth();

	/// \brief R树维度
	int Dimension();

	/// \brief 根据矩形范围查询相交对象id
	/// \param box 要检索的矩形范围
	/// \param vecResult 返回和检索矩形相交的对象id
	/// \return 返回是否检索到对象
	virtual bool Query(const GsBox& box,GsVector<int> &vecResult);
	/// \brief 增加一个对象到空间索引
	/// \param box 要增加对象的box
	/// \param nID 要增加对象的id
	/// \return 增加是否成功
	virtual bool Add(const GsBox& box,int nID);
	/// \brief 从空间索引移除一个对象
	/// \param nID 要移除对象的id
	/// \return 移除是否成功
	virtual bool Remove(int nID);

	/// \brief 将索引保存为QIX文件
	/// \details 将内存的索引保存为文件，可以通过GsQIXFileSpatialIndex类打开快速检索。
	/// \param strQIXFile 要保存的文件路径
	void SaveToQIXFile(const char* strQIXFile);

	/// \brief 查询多个维度
	/// \param minBound 维度最小的值
	/// \param maxBound 维度最大的值
	/// \param nDim 要检索的维度
	/// \return 返回是否检索到对象
	virtual bool QueryMultiDimension(const double* minBound,const double* maxBound,int nDim,GsVector<int> &vecResult);
	
};
/// \brief GsMemoryRTreeSpatialIndexPtr
GS_SMARTER_PTR(GsMemoryRTreeSpatialIndex);


/// \brief 基于本地QIX文件的只读R树空间索引
class GS_API GsQIXFileSpatialIndex:public GsSpatialIndexQuery
{
	void* m_pQIXHandle;
public:
	/// \brief 从QIX文件名构造
	GsQIXFileSpatialIndex(const char* strQIXFile);
	~GsQIXFileSpatialIndex();

	/// \brief 根据矩形范围查询相交对象id
	/// \param box 要检索的矩形范围
	/// \param vecResult 返回和检索矩形相交的对象id
	/// \return 返回是否检索到对象
	virtual bool Query(const GsBox& box,GsVector<int> &vecResult);
	 
	/// \brief 查询多个维度
	/// \param minBound 维度最小的值
	/// \param maxBound 维度最大的值
	/// \param nDim 要检索的维度
	/// \return 返回是否检索到对象
	virtual bool QueryMultiDimension(const double* minBound,const double* maxBound,int nDim,GsVector<int> &vecResult);
	
};
/// \brief GsQIXFileSpatialIndexPtr
GS_SMARTER_PTR(GsQIXFileSpatialIndex);


KERNEL_ENDNS
