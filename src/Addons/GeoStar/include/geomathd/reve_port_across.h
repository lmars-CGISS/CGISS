// reve_port_across.h: interface for the reve_port_across class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PORT_ACROSS_H__7EF6632F_42AB_4F14_B763_22D2F52663E0__INCLUDED_)
#define AFX_PORT_ACROSS_H__7EF6632F_42AB_4F14_B763_22D2F52663E0__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class point_map;

class GEO_DLL reve_port_across  
{
    std::vector<double*>        m_add;
    std::vector<double*>        m_remove;

    bool                        m_update;
    void                        update();
public:
	reve_port_across();
	virtual ~reve_port_across();
    
    void add(const path *l);
    void remove(const path *l);

    int across(point pt)const;

    int across(point pt,const point_map *filter,const void* key)const;

    int across(point pt,std::vector<void*> &A)const;
};

GEO_NAMESPACE_END

#endif // !defined(AFX_PORT_ACROSS_H__7EF6632F_42AB_4F14_B763_22D2F52663E0__INCLUDED_)
