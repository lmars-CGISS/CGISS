#pragma once
#include "preconfig.h" 
#include "stringhelp.h"
#include <memory>
#include "memorymanager.h"

UTILITY_NS 
/// \brief ZIP文件上下文。
struct GS_API GsZipContext
{
	void* Zip;
	GsZipContext(void* z);
	~GsZipContext();
};
typedef std::shared_ptr<GsZipContext> GsZipContextPtr;
typedef std::weak_ptr<GsZipContext> GsZipContextWPtr;

/// \brief GsZipSource操作命令
enum GsZipCommand{
    eZIP_SOURCE_OPEN,            /* prepare for reading */
    eZIP_SOURCE_READ,            /* read data */
    eZIP_SOURCE_CLOSE,           /* reading is done */
    eZIP_SOURCE_STAT,            /* get meta information */
    eZIP_SOURCE_ERROR,           /* get error information */
    eZIP_SOURCE_FREE,            /* cleanup and free resources */
    eZIP_SOURCE_SEEK,            /* set position for reading */
    eZIP_SOURCE_TELL,            /* get read position */
    eZIP_SOURCE_BEGIN_WRITE,     /* prepare for writing */
    eZIP_SOURCE_COMMIT_WRITE,    /* writing is done */
    eZIP_SOURCE_ROLLBACK_WRITE,  /* discard written changes */
    eZIP_SOURCE_WRITE,           /* write data */
    eZIP_SOURCE_SEEK_WRITE,      /* set position for writing */
    eZIP_SOURCE_TELL_WRITE,      /* get write position */
    eZIP_SOURCE_SUPPORTS,        /* check whether source supports command */
    eZIP_SOURCE_REMOVE           /* remove file */
};

/// \brief Zip数据源。
class GS_API GsZipSource
{
	
public:
	virtual ~GsZipSource(){}
	virtual long long Call(void* pBuffer,int nLen,int command) = 0;
};

/// \brief zip压缩文件内的一个文件或者目录。
class GS_API GsZipEntry
{
	GsZipContextWPtr m_ptrHandle; 
	/// \brief 压缩文件的索引
	long long	m_Index;
	/// \brief 路径和名称
	GsString	m_Name;
	/// \brief 文件的实际大小
	long long	m_Size;		
    /// \brief 文件的压缩大小
	long long	m_CompSize;	
    
	/// \brief 解压文件时的读取句柄。
	void* m_Handle;
public:
	GsZipEntry();
	GsZipEntry(GsZipContextPtr &ptrHandle,int nIndex);
	GsZipEntry(const GsZipEntry& rhs);
	~GsZipEntry();
	GsString Name()const;
	/// \brief 文件索引
	int Index()const;
	/// \brief 未压缩大小
	int UncompressedSize()const;
	/// \brief 压缩后大小
	int CompressedSize()const;
	/// \brief 路径
	GsString Path()const;
	/// \brief 是否是目录
	bool IsFolder()const;
	/// \brief 是否有效
	bool IsValid()const;
	/// \brief 是否有效
	operator bool() const;

	GsZipEntry& operator = (const GsZipEntry& rhs);

	/// \brief 开始读取数据
	bool BeginRead();

	/// \brief 读取一段数据返回读取的字节。返回0标识或者小于输入Buffer长度则标识读取完成。
	int Read(unsigned char* buff,int nLen);

	/// \brief 读取结束读取
	bool EndRead();

	/// \brief 读取所有数据到这个源中
	bool ReadTo(GsZipSource* source);

	/// \brief 读取所有数据到这个源中
	bool ReadTo(GsByteBuffer* source);

	/// \brief 删除自身。
	bool Delete();

};
/// \brief zip文件封装类。
class GS_API GsZipFile
{
	GsZipContextPtr m_ptrHandle;
	int m_Error;
public:
	/// \brief 从内存中解压zip文件
	GsZipFile(const unsigned char* data,int nLen);
	/// \brief 从自定义源中解压zip文件
	GsZipFile(GsZipSource* zipSource);
	/// \brief 从文件解压或者创建新的zip文件
	GsZipFile(const char* file);
	virtual ~GsZipFile(void);
	/// \brief zip文件中打包文件的数量
	int EntryCount();

	/// \brief 根据索引获得一个文件
	GsZipEntry Entry(int i);

	/// \brief 根据名称获得一个文件
	GsZipEntry Entry(const char* name);

	/// \brief 向Zip文件中添加一个文件
	bool Add(const char* name,const char* localfile);

	/// \brief 向Zip文件中添加自定义源的文件。
	bool Add(const char* name,GsZipSource* source);

	/// \brief 向Zip文件中内存块作为文件。
	bool Add(const char* name,const char* blob,int nLen);

};


/// \brief zlib功能封装
class GS_API GsZLib
{
public:
	/// \brief 压缩一段内存
	/// \param nLevel 压缩级别0~9,  0标识不压缩，9标识最大压缩
	static int Compress (const unsigned char *source, unsigned int sourceLen,
						unsigned char *dest,   unsigned int &destLen ,int nLevel=6);
	
	/// \brief 压缩一段内存
	/// \param nLevel 压缩级别0~9,  0标识不压缩，9标识最大压缩
	static int Compress (GsByteBuffer* input,  GsByteBuffer* output,int nLevel=6);

	/// \brief 解压一段内存
	static int Uncompress(GsByteBuffer* input,  GsByteBuffer* output);

	/// \brief 解压一段内存
	/// \param sourceLen 要解压的内存大小，返回时返回解压了多长的长度。
	static int Uncompress(const unsigned char *source, unsigned int& sourceLen,  GsByteBuffer* output);

};

/// \brief GZ压缩功能
class GS_API GsGZFile
{
public:
	GsGZFile(const char* gzfile);
	~GsGZFile();

};

UTILITY_ENDNS