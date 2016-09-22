// surface_unions.h: interface for the surface_unions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURFACE_UNIONS_H__DC6D9F4E_2E2A_49D9_8DF9_320656C6EDCB__INCLUDED_)
#define AFX_SURFACE_UNIONS_H__DC6D9F4E_2E2A_49D9_8DF9_320656C6EDCB__INCLUDED_

#include "path.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class GEO_DLL surface_unions  
{
	multi_path	m_stack;
	int			m_count;
public:
	surface_unions();
	~surface_unions();
	void clear();
	void add(path *a);
	path_ptr result();
};

GEO_NAMESPACE_END

#endif // !defined(AFX_SURFACE_UNIONS_H__DC6D9F4E_2E2A_49D9_8DF9_320656C6EDCB__INCLUDED_)
