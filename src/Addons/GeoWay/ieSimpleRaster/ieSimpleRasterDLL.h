#ifndef _IE_SINPLE_RASTER_DLL_H
#define _IE_SINPLE_RASTER_DLL_H
#pragma once

#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include <string>
#include <vector>


#include <windows.h>

#ifdef  IESIMPLERASTER_EXPORTS
#define IE_SIMPLE_RASTER_EXT_CLASS	__declspec(dllexport)
#else
#define IE_SIMPLE_RASTER_EXT_CLASS	__declspec(dllimport)
#endif

#endif