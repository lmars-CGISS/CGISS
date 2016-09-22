#pragma once
#include "preconfig.h" 
#include "object.h" 
#include <utility>
#include "stringhelp.h"
UTILITY_NS
	
/// \brief GsAny对象的数据类型
enum GsVarType
{
	/// \brief 空数据
	eEmpty=-1,
	/// \brief char
	eI1=0,
	/// \brief short
	eI2,
	/// \brief int
	eI4,
	/// \brief long long
	eI8,
	/// \brief unsigned char
	eUI1,
	/// \brief unsigned short
	eUI2,
	/// \brief unsigned int
	eUI4,
	/// \brief unsigned long long
	eUI8,
	/// \brief float
	eR4,
	/// \brief double
	eR8,
	/// \brief const char*
	eString,
	/// \brief bool
	eBool,
	/// \brief GsRefObject*
	eObject,
	/// \brief 二进制数据
	eBlob,
};
 

/// \brief 存储各种类型数据的对象。
class  GS_API GsAny
{
public:
	/// \brief 数据类型
	GsVarType Type;
	/// \brief 数据联合体
	union
	{
		char			cVal;
		unsigned char	ucVal;
		short			sVal;
		unsigned short	usVal;
		int				iVal;
		unsigned int	uiVal;
		long long		llVal;
		unsigned long long ullVal;
		float			fltVal;
		double			dblVal;
		bool			boolVal;
		GsRefObject*		objVal;
		char*			strVal;
		unsigned char* blbVal;
	};
	virtual ~GsAny();
	
	/// \brief 构造函数重载
	GsAny();
	/// \brief 单字符构造函数
	GsAny(char v);
	/// \brief 无符号字符构造函数
	GsAny(unsigned char v);
	/// \brief 16位的构造函数
	GsAny(short v);
	/// \brief 无符号16位的构造函数
	GsAny(unsigned short v);
	/// \brief 32位的构造函数
	GsAny(int v);
	/// \brief 无符号32位的构造函数
	GsAny(unsigned int v);
	/// \brief 64位的构造函数
	GsAny(long long v);
	/// \brief 无符号64位的构造函数
	GsAny(unsigned long long v);
	/// \brief 32位浮点构造函数
	GsAny(float v);
	/// \brief 64位浮点构造函数
	GsAny(double v);
	/// \brief bool类型构造函数
	GsAny(bool v);
	/// \brief GsRefObject类指针的构造函数
	GsAny(GsRefObject* v);
	/// \brief 字符常量构造函数
	GsAny(const char* v);
	/// \brief 无符号字符常量构造函数
	GsAny(const unsigned char* v,int nLen);
	/// \brief 类引用构造函数
	GsAny(const GsAny& rhs);

	/// \brief 符号重载，返回引用类型
	GsAny& operator =(const GsAny& rhs);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(char v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(unsigned char v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(short v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(unsigned short v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(int v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(unsigned int v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(long long v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(unsigned long long v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(float v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(double v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(bool v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(const char* v);
	/// \brief 符号重载，返回引用类型
	GsAny& operator =(GsRefObject* v);

	void Clear();
	
	/// \brief 类型转换
	operator char();
	/// \brief 类型转换
	operator unsigned char();
	/// \brief 类型转换
	operator short();
	/// \brief 类型转换
	operator unsigned short();
	/// \brief 类型转换
	operator int();
	/// \brief 类型转换
	operator unsigned int();
	/// \brief 类型转换
	operator long long();
	/// \brief 类型转换
	operator unsigned long long();
	/// \brief 类型转换	
	operator bool();
	/// \brief 类型转换
	operator float();
	/// \brief 类型转换
	operator double();
	/// \brief 类型转换
	operator char*();
	/// \brief 类型转换
	operator GsRefObject*();

	
	/// \brief 设置blob数据
	void Set(const unsigned char* bBlob,int nLen);

	/// \brief 分配空的blob空间，并设置类型为blob
	void AllocBlob(int nLen);

	/// \brief 数据的大小
	///\return 返回数据的长度
 	int ValueSize();

	/// \brief 数据的头指针
	///\return 返回数据的头指针地址
 	void* ValuePtr();

	
	/// \brief 计算对象的哈希值
	///\return 返回哈希值。
	unsigned long long HashCode();


};


/// \brief 各类数据计算为Hash值
class GS_API GsHash
{
public:
	/// \brief 任意内存块计算64位Hash
	static unsigned long long Hash64(unsigned char* blob,int nLen);

	/// \brief 任意内存块计算128位Hash
	static std::pair<unsigned long long,unsigned long long> Hash128(unsigned char* blob,int nLen);

	/// \brief 任意内存块计算MD5
	static GsString MD5(unsigned char* blob,int nLen);

	/// \brief 计算文件MD5
	static GsString MD5(const char* strFile);
};

UTILITY_ENDNS
