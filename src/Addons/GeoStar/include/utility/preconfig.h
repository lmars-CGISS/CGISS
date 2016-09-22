#pragma once
#define UTILITY_NS namespace GeoStar{namespace Utility{
#define UTILITY_ENDNS }}

#define UTILITY_NAME GeoStar::Utility

#define KERNEL_NS namespace GeoStar{namespace Kernel{
#define KERNEL_ENDNS }}
#define KERNAL_NAME GeoStar::Kernel

#ifndef GS_API
#if defined(GEOSTAR_DLL)
    #if defined(WIN32)
        #if GEOSTAR_IMPLEMENTATION
            #define GS_API __declspec(dllexport)
        #else
            #define GS_API __declspec(dllimport)
        #endif
    #else
        #define GS_API __attribute__((visibility("default")))
    #endif
#else
    #define GS_API
#endif
#endif


#ifdef _MSC_VER
#pragma warning(disable : 4018)

#pragma warning(disable : 4100)
#pragma warning(disable : 4101)
#pragma warning(disable : 4189)
#pragma warning(disable : 4192)

#pragma warning(disable : 4238)
#pragma warning(disable : 4239)
#pragma warning(disable : 4244)
#pragma warning(disable : 4245)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)


#pragma warning(disable : 4305)
#pragma warning(disable : 4311)
#pragma warning(disable : 4389)

#pragma warning(disable : 4482)
#pragma warning(disable : 4635) 
#pragma warning(disable : 4701)

#pragma warning(disable : 4800)
 

#endif

#include <stdio.h>
#include <memory>


#ifdef linux
#include "limits.h"
#ifdef _LP64
#define INT3264_MAX LONG_LONG_MAX
#else
#define INT3264_MAX INT_MAX
#endif
  


typedef long long __int64; 
typedef long __int3264; 
#else
#ifdef _WIN64
#define INT3264_MAX _I64_MAX
#else
#define INT3264_MAX INT_MAX
#endif
#endif