// geo_io.h: interface for the geo_io class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEO_IO_H__EC6C0099_9C41_49C7_9F61_FDB11F0551B7__INCLUDED_)
#define AFX_GEO_IO_H__EC6C0099_9C41_49C7_9F61_FDB11F0551B7__INCLUDED_

#include <istream>
#include <ostream>
#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//描述：将point、pnode输出到流中
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::point& pt);
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::pnode& pt);

//描述：将path输出到流中，这个函数只输出坐标的信息不输出id和类型信息
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::path& l);

//描述：将path输出到流中，这个函数输出类型信息、id、和path的坐标信息。外部应该调用这个函数
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::path* l);

//描述：从流中读取point、pnode信息
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::point &pt);
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::pnode &pt);

//描述：从流中读取path，这个函数要求传入的l以及正确创建，它只读取坐标信息
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::path &l);

//描述：从流中读取path，这个函数函数会读取类型信息id，然后创建合适的path，最后读取坐标信息
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::path_ptr &l);


#endif // !defined(AFX_GEO_IO_H__EC6C0099_9C41_49C7_9F61_FDB11F0551B7__INCLUDED_)
