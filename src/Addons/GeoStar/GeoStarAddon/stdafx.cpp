// stdafx.cpp : 只包括标准包含文件的源文件
// GeoStarAddon.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用
//#pragma comment(lib,"gdal_i.lib")
#ifdef _DEBUG
#pragma comment(lib,"geodatabased.lib")
#pragma comment(lib,"spatialreferenced.lib")
#pragma comment(lib,"geometryd.lib")
#pragma comment(lib,"utilityd.lib")
#else
#pragma comment(lib,"geodatabase.lib")
#pragma comment(lib,"spatialreference.lib")
#pragma comment(lib,"geometry.lib")
#pragma comment(lib,"utility.lib")
#endif

#pragma comment(lib,"libgpkg.lib")