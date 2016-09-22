// geomacro.h: interface for the geomacro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMACRO_H__F847D578_BC17_4513_8E04_13DE0F4D1D8A__INCLUDED_)
#define AFX_GEOMACRO_H__F847D578_BC17_4513_8E04_13DE0F4D1D8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef WIN32
#pragma warning (disable:4275)
#pragma warning (disable:4251)
#pragma warning (disable:4522)
#pragma warning (disable:4786)
#pragma warning (disable:4311 4312)
#endif

#include <float.h>
#include <math.h>
#include <vector>
#include <functional>

#ifndef PI
#define PI 3.1415926535897932
#endif

#ifndef GEO_DLL
#ifdef _WIN32
#define GEO_DLL __declspec( dllimport )
#else
#define GEO_DLL
#endif
#endif

#if _MSC_VER < 1300
#define GEO_DLL_CMF GEO_DLL
#else
#define GEO_DLL_CMF 
#endif

#define GEO_NAMESPACE_BEGIN namespace GeoStar{namespace Kernel{namespace SpatialAnalysis{
#define GEO_NAMESPACE_END }}}

#define GEO_NAMESPACE GeoStar::Kernel::SpatialAnalysis
#define SPATIALANALYSIS_NS GEO_NAMESPACE
#define GEOMATHD_NS GEO_NAMESPACE




#endif // !defined(AFX_GEOMACRO_H__F847D578_BC17_4513_8E04_13DE0F4D1D8A__INCLUDED_)
