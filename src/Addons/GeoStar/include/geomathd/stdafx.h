// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E60C1C58_4017_43C6_853D_C1B94FA88DCF__INCLUDED_)
#define AFX_STDAFX_H__E60C1C58_4017_43C6_853D_C1B94FA88DCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#define GEO_DLL __declspec( dllexport )
#endif
#include <preconfig.h>


#pragma warning (disable:4786)
#pragma warning (disable:4018)
#pragma warning (disable:4996)
#pragma warning (disable:4244)
#pragma warning (disable:4267)
 

#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <memory.h>



#define GEOMATH_LIB

#include "std6.0.h"

inline FILE* tmpfile_c(){
	FILE* tmp=0; 
#if _MSC_VER < 1400
	tmp = tmpfile();
#else
	tmpfile_s(&tmp);
#endif
	return tmp;
}
template<class type> type geo_max(type a,type b){ return a>b?a:b; }
template<class type> type geo_min(type a,type b){ return a<b?a:b; }
#ifdef _WIN64
#define _LP64 1
#endif

#ifdef _LP64
#define GEOMATHD64
#endif

//#define GEO_DLL 
 
// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E60C1C58_4017_43C6_853D_C1B94FA88DCF__INCLUDED_)
