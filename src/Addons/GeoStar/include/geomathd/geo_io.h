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

//��������point��pnode���������
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::point& pt);
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::pnode& pt);

//��������path��������У��������ֻ����������Ϣ�����id��������Ϣ
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::path& l);

//��������path��������У�����������������Ϣ��id����path��������Ϣ���ⲿӦ�õ����������
GEO_DLL std::ostream& operator << (std::ostream &out,const GEO_NAMESPACE::path* l);

//�����������ж�ȡpoint��pnode��Ϣ
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::point &pt);
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::pnode &pt);

//�����������ж�ȡpath���������Ҫ�����l�Լ���ȷ��������ֻ��ȡ������Ϣ
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::path &l);

//�����������ж�ȡpath����������������ȡ������Ϣid��Ȼ�󴴽����ʵ�path������ȡ������Ϣ
GEO_DLL std::istream& operator >> (std::istream &out,GEO_NAMESPACE::path_ptr &l);


#endif // !defined(AFX_GEO_IO_H__EC6C0099_9C41_49C7_9F61_FDB11F0551B7__INCLUDED_)
