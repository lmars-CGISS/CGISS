#pragma once
#include "preconfig.h" 
#include "stringhelp.h"
#include <iostream>
#include <iosfwd>
#include <streambuf>
UTILITY_NS 

/// \brief 直接内存块
class GS_API GsByteBuffer
{
protected:
	/// \brief 受保护的构造函数，只有子类才能创建对象
	GsByteBuffer();
public:
	virtual ~GsByteBuffer();

	/// \brief 类型转换重载函数，转换为无符号字符指针类型
	virtual operator unsigned char* ()const = 0; 	
	/// \brief 类型转换重载函数，转换为字符指针类型
	virtual operator char* ()const;
	/// \brief 类型转换重载函数，转换为整数指针类型
	virtual operator int* ()const;
	/// \brief 类型转换重载函数，转换为无符号整数指针类型
	virtual operator unsigned int* ()const;
	/// \brief 类型转换重载函数，转换为16位整数指针类型
	virtual operator short* ()const;
	/// \brief 类型转换重载函数，转换为无符号16位整数指针类型
	virtual operator unsigned short* ()const;
	/// \brief 类型转换重载函数，转换为64位整数指针类型
	virtual operator long long* ()const;
	/// \brief 类型转换重载函数，转换为无符号64位整数指针类型
	virtual operator unsigned long long* ()const;
	/// \brief 类型转换重载函数，转换为64位浮点指针类型
	virtual operator double* ()const;
	/// \brief 类型转换重载函数，转换为32位浮点指针类型
	virtual operator float* ()const;
	/// \brief 类型转换重载函数，转换为BOOL指针类型
	virtual operator bool* ()const;
	
	/// \brief 缓冲区的头指针，相当于BufferHead()
	virtual unsigned char* Ptr() const= 0; 
	
	/// \brief 缓冲区的尾指针
	/// \details >=此指针表示超出了缓冲区范围
	virtual unsigned char* EndPtr() const; 
	
	/// \brief 函数模板
	template<typename T>
	T* PtrT() const
	{
		return (T*)(Ptr());
	}

	/// \brief 函数模板
	template<typename T>
	T* EndPtrT() const
	{
		return (T*)(EndPtr());
	}

	/// \brief 缓冲区的头指针
	virtual unsigned char* BufferHead()const = 0;
	/// \brief 缓冲区的长度
	virtual unsigned int BufferSize() const= 0;
	
	/// \brief 依照结构类型计算的元素数量
	template<typename T>
	unsigned int BufferSizeT() const
	{
		return BufferSize() / sizeof(T);
	}

	/// \brief 设置缓冲区的字节值为特定值
	///\details 类似memset的功能
	virtual unsigned char* SetBufferValue(int nValue) = 0;

	/// \brief 依照结构类型计算的元素数量
	template<typename T>
	T* SetBufferValueT(const T& val)
	{
		//获取数据的字节
		const unsigned char* pByte = (const unsigned char* )&val;
		//判断整个数据为重复字节，或者全部为0
		bool bIsEqual = true;
		for(int i =1;i<sizeof(val);i++)
		{
			if(pByte[i] != pByte[0])
			{
				bIsEqual = false;
				break;
			}
		}
		//如果整个为重复字节。
		if(bIsEqual)
			return (T*)SetBufferValue(pByte[0]);
		//如果是非重复字节这需要租个赋值
		T* pHead = PtrT<T>();
		T* pEnd = EndPtrT<T>();
		for(;pHead < pEnd;pHead++)
		{
			pHead[0] = val;
		}
		return PtrT<T>();
	}

	/// \brief 向尾部添加一段数据
	virtual unsigned char* Append(const unsigned char* pBuff,int nLen) = 0;
	/// \brief 向尾部增加一段字符串
	virtual unsigned char* Append(const char* pStr) = 0;
	/// \brief 向尾部增加一段特定结构的数组
	template<typename T>
	unsigned char* AppendT(const T* pBuff,int nLen)
	{
		return Append((const unsigned char*)pBuff,nLen * sizeof(T)); 
	}
	/// \brief 向尾部增加一个特定结构数据
	template<typename T>
	unsigned char* AppendT(const T& pBuff)
	{
		return Append((const unsigned char*)&pBuff,sizeof(T)); 
	}
	/// \brief 从特定位置覆盖数据
	virtual unsigned char* Insert(unsigned int nPos,const unsigned char* pStr,int nLen) = 0;
	/// \brief 分配特定字节长度的缓冲区。
	virtual unsigned char* Allocate(unsigned int nLen) = 0;
	/// \brief 函数模板，分配内存
	template<typename T>
	T* AllocateT(int nLen)
	{
		Allocate(sizeof(T) * nLen);
		return PtrT<T>();
	}
	/// \brief 清除内存数据
	virtual void Clear() = 0;
	/// \brief 释放内存
	virtual void Reset() = 0;
	/// \brief 复制输入内存块中特定长度的数据
	virtual unsigned char* Copy(const unsigned char* pBuff,int nLen) = 0; 	
	
	/// \brief 将二进制内存块转换为base64编码字符串
	GsString ToBase64()const;

	/// \brief 从Base64字符串解码成为内存块
	bool FromBase64(const char* strBase64);

};



/// \brief 增长型直接内存块，内存只增加不减少
class GS_API GsGrowByteBuffer:public GsByteBuffer
{
	/// \brief 联合体
	union{
		unsigned char* m_pBuffer;
		/// \brief 结构体，m_pMeta为结构体类型的指针
		struct
		{
			unsigned int Real;
			unsigned int Size;
		}* m_pMeta; 
	};
public:
	GsGrowByteBuffer(int nLen = 0);
	/// \brief 构造函数，传递指针地址给类成员变量
	GsGrowByteBuffer(unsigned char* pBuffer);
	/// \brief 构造函数，分配nLen个字符内存
	GsGrowByteBuffer(const unsigned char* pBuffer,int nLen);
	virtual ~GsGrowByteBuffer();
	/// \brief 释放内存，传递指针地址
	void Attach(unsigned char* pBuffer);
	/// \brief 传递指针地址
	unsigned char* Detach();
	/// \brief 类型转换
	virtual operator unsigned char* () const;
	/// \brief 分配8个字符内存
	virtual unsigned char* Ptr() const;
	/// \brief 分配8个字符内存
	virtual unsigned char* BufferHead()const ;
	/// \brief 分配nLen个字符内存
	virtual unsigned int BufferSize() const;
	virtual unsigned int RealSize() const;
	/// \brief 复制int类型数据的前real个字节
	virtual unsigned char* SetBufferValue(int nValue) ;
	/// \brief 增加内存
	virtual unsigned char* Append(const unsigned char* pBuff,int nLen) ;
	/// \brief 函数重载，增加内存
	virtual unsigned char* Append(const char* pStr) ;
	virtual unsigned char* Insert(unsigned int nPos,const unsigned char* pStr,int nLen) ;
	/// \brief 分配nLen个字节内存
	virtual unsigned char* Allocate(unsigned int nLen) ;
	/// \brief 清除内存数据
	virtual void Clear() ;
	/// \brief 释放内存
	virtual void Reset() ;
	/// \brief 复制nLen个字节
	virtual unsigned char* Copy(const unsigned char* pBuff,int nLen) ; 

	/// \brief 交换两个缓冲区的数据
	GsGrowByteBuffer* Swap(GsGrowByteBuffer& rhs);



}; 

/// \brief 将bytebuffer作为stl标准流来处理。
class GS_API GsByteBufferStream :public std::iostream
{
	class StreamReBuffer : public std::streambuf
	{
		GsByteBuffer* m_pBuffer;
		long long m_Position;
	public:
		StreamReBuffer(GsByteBuffer* pBuffer);
	protected:
		std::streamsize xsputn(
			const char* s,
			std::streamsize num
			);

		std::streamsize xsgetn(
			char* s,
			std::streamsize n
			);
	};
	StreamReBuffer m_Buff;
public:
	GsByteBufferStream(GsByteBuffer* pBuffer);

};

UTILITY_ENDNS