// point.h: interface for the point class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "geomacro.h"

GEO_NAMESPACE_BEGIN
	class path;
	class polyline;
	class curve;
	class multi_path;
#ifndef GEOMATHD64
#ifdef _LP64
#define GEOMATHD64
#endif
#endif

#ifdef GEOMATHD64

template<class type> type safe_ptr(type ptr){
	return (type)(((long long)ptr)&0xFffffffffffffffC);
}

template<class type> type safe_ptr_ex(type ptr){
    return (type)(((long long)ptr)&0xFffffffffffffffc);
}

template<class type> type reve_ptr(type ptr){
    return ptr?(type)(((long long)ptr)^0x0000000000000001):0;
}

inline void* mask_ptr(const void* ptr,int mask){ 
	return (void*)(((long long)ptr)|mask); 
}

template<class type>
inline bool is_marked(type ptr){
    return ((long long)ptr)&0x0000000000000001?true:false;
}
//ptr 为path_prop::item 类型
inline bool is_marked_pp_item(const void* ptr){
    return ((long long)ptr)&0x00000001?true:false;
}

#else 

template<class type> type safe_ptr(type ptr){
    return (type)(((int)ptr)&0xFFFFFFFC);
}
inline path* safe_ptr(const path* ptr){
    return (path*)(((int)ptr)&0xFFFFFFFC);
}
inline polyline* safe_ptr(const polyline* ptr){
    return (polyline*)(((int)ptr)&0xFFFFFFFC);
}
inline curve* safe_ptr(const curve* ptr){
    return (curve*)(((int)ptr)&0xFFFFFFFC);
}
inline multi_path* safe_ptr(const multi_path* ptr){
    return (multi_path*)(((int)ptr)&0xFFFFFFFC);
}

inline path* safe_ptr(path* ptr){
    return (path*)(((int)ptr)&0xFFFFFFFC);
}
inline polyline* safe_ptr(polyline* ptr){
    return (polyline*)(((int)ptr)&0xFFFFFFFC);
}
inline curve* safe_ptr(curve* ptr){
    return (curve*)(((int)ptr)&0xFFFFFFFC);
}
inline multi_path* safe_ptr(multi_path* ptr){
    return (multi_path*)(((int)ptr)&0xFFFFFFFC);
}

template<class type> type safe_ptr_ex(type ptr){
    return (type)(((int)ptr)&0xFFFFFFFC);
}

template<class type> type reve_ptr(type ptr){
    return ptr?(type)(((int)ptr)^0x00000001):0;
}
inline path* reve_ptr(const path* ptr){
    return ptr?(path*)(((int)ptr)^0x00000001):0;
}
inline curve* reve_ptr(const curve* ptr){
    return ptr?(curve*)(((int)ptr)^0x00000001):0;
}
inline polyline* reve_ptr(const polyline* ptr){
    return ptr?(polyline*)(((int)ptr)^0x00000001):0;
}
inline multi_path* reve_ptr(const multi_path* ptr){
    return ptr?(multi_path*)(((int)ptr)^0x00000001):0;
}

inline path* reve_ptr(path* ptr){
    return ptr?(path*)(((int)ptr)^0x00000001):0;
}
inline curve* reve_ptr(curve* ptr){
    return ptr?(curve*)(((int)ptr)^0x00000001):0;
}
inline polyline* reve_ptr(polyline* ptr){
    return ptr?(polyline*)(((int)ptr)^0x00000001):0;
}
inline multi_path* reve_ptr(multi_path* ptr){
    return ptr?(multi_path*)(((int)ptr)^0x00000001):0;
}



inline void* mask_ptr(const void* ptr,int mask){ 
	return (void*)(((int)ptr)|mask); 
}

template<class type>
inline bool is_marked(type ptr){
    return ((int)ptr)&0x00000001?true:false;
} 

inline bool is_marked(const path* ptr){
    return ((int)ptr)&0x00000001?true:false;
}

//ptr 为path_prop::item 类型
inline bool is_marked_pp_item(const void* ptr){
    return ((int)ptr)&0x00000001?true:false;
}

inline bool is_marked(path* ptr){
    return ((int)ptr)&0x00000001?true:false;
}  

#endif
 

GEO_NAMESPACE_END

	