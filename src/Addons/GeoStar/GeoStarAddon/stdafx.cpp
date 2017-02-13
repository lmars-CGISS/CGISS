// stdafx.cpp : 只包括标准包含文件的源文件
// GeoStarAddon.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用
//#pragma comment(lib,"gdal_i.lib")
#ifdef _DEBUG
#pragma comment(lib,"gsgeodatabased.lib")
#pragma comment(lib,"gsspatialreferenced.lib")
#pragma comment(lib,"gsgeometryd.lib")
#pragma comment(lib,"gsutilityd.lib")
#else
#pragma comment(lib,"gsgeodatabase.lib")
#pragma comment(lib,"gsspatialreference.lib")
#pragma comment(lib,"gsgeometry.lib")
#pragma comment(lib,"gsutility.lib")
#endif

#pragma comment(lib,"libgpkg.lib")