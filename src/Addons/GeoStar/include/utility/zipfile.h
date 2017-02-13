#pragma once
#include "preconfig.h" 
#include "stringhelp.h"
#include <memory>
#include "memorymanager.h"

UTILITY_NS 
/// \brief ZIP�ļ������ġ�
struct GS_API GsZipContext
{
	void* Zip;
	GsZipContext(void* z);
	~GsZipContext();
};
typedef std::shared_ptr<GsZipContext> GsZipContextPtr;
typedef std::weak_ptr<GsZipContext> GsZipContextWPtr;

/// \brief GsZipSource��������
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

/// \brief Zip����Դ��
class GS_API GsZipSource
{
	
public:
	virtual ~GsZipSource(){}
	virtual long long Call(void* pBuffer,int nLen,int command) = 0;
};

/// \brief zipѹ���ļ��ڵ�һ���ļ�����Ŀ¼��
class GS_API GsZipEntry
{
	GsZipContextWPtr m_ptrHandle; 
	/// \brief ѹ���ļ�������
	long long	m_Index;
	/// \brief ·��������
	GsString	m_Name;
	/// \brief �ļ���ʵ�ʴ�С
	long long	m_Size;		
    /// \brief �ļ���ѹ����С
	long long	m_CompSize;	
    
	/// \brief ��ѹ�ļ�ʱ�Ķ�ȡ�����
	void* m_Handle;
public:
	GsZipEntry();
	GsZipEntry(GsZipContextPtr &ptrHandle,int nIndex);
	GsZipEntry(const GsZipEntry& rhs);
	~GsZipEntry();
	GsString Name()const;
	/// \brief �ļ�����
	int Index()const;
	/// \brief δѹ����С
	int UncompressedSize()const;
	/// \brief ѹ�����С
	int CompressedSize()const;
	/// \brief ·��
	GsString Path()const;
	/// \brief �Ƿ���Ŀ¼
	bool IsFolder()const;
	/// \brief �Ƿ���Ч
	bool IsValid()const;
	/// \brief �Ƿ���Ч
	operator bool() const;

	GsZipEntry& operator = (const GsZipEntry& rhs);

	/// \brief ��ʼ��ȡ����
	bool BeginRead();

	/// \brief ��ȡһ�����ݷ��ض�ȡ���ֽڡ�����0��ʶ����С������Buffer�������ʶ��ȡ��ɡ�
	int Read(unsigned char* buff,int nLen);

	/// \brief ��ȡ������ȡ
	bool EndRead();

	/// \brief ��ȡ�������ݵ����Դ��
	bool ReadTo(GsZipSource* source);

	/// \brief ��ȡ�������ݵ����Դ��
	bool ReadTo(GsByteBuffer* source);

	/// \brief ɾ������
	bool Delete();

};
/// \brief zip�ļ���װ�ࡣ
class GS_API GsZipFile
{
	GsZipContextPtr m_ptrHandle;
	int m_Error;
public:
	/// \brief ���ڴ��н�ѹzip�ļ�
	GsZipFile(const unsigned char* data,int nLen);
	/// \brief ���Զ���Դ�н�ѹzip�ļ�
	GsZipFile(GsZipSource* zipSource);
	/// \brief ���ļ���ѹ���ߴ����µ�zip�ļ�
	GsZipFile(const char* file);
	virtual ~GsZipFile(void);
	/// \brief zip�ļ��д���ļ�������
	int EntryCount();

	/// \brief �����������һ���ļ�
	GsZipEntry Entry(int i);

	/// \brief �������ƻ��һ���ļ�
	GsZipEntry Entry(const char* name);

	/// \brief ��Zip�ļ������һ���ļ�
	bool Add(const char* name,const char* localfile);

	/// \brief ��Zip�ļ�������Զ���Դ���ļ���
	bool Add(const char* name,GsZipSource* source);

	/// \brief ��Zip�ļ����ڴ����Ϊ�ļ���
	bool Add(const char* name,const char* blob,int nLen);

};


/// \brief zlib���ܷ�װ
class GS_API GsZLib
{
public:
	/// \brief ѹ��һ���ڴ�
	/// \param nLevel ѹ������0~9,  0��ʶ��ѹ����9��ʶ���ѹ��
	static int Compress (const unsigned char *source, unsigned int sourceLen,
						unsigned char *dest,   unsigned int &destLen ,int nLevel=6);
	
	/// \brief ѹ��һ���ڴ�
	/// \param nLevel ѹ������0~9,  0��ʶ��ѹ����9��ʶ���ѹ��
	static int Compress (GsByteBuffer* input,  GsByteBuffer* output,int nLevel=6);

	/// \brief ��ѹһ���ڴ�
	static int Uncompress(GsByteBuffer* input,  GsByteBuffer* output);

	/// \brief ��ѹһ���ڴ�
	/// \param sourceLen Ҫ��ѹ���ڴ��С������ʱ���ؽ�ѹ�˶೤�ĳ��ȡ�
	static int Uncompress(const unsigned char *source, unsigned int& sourceLen,  GsByteBuffer* output);

};

/// \brief GZѹ������
class GS_API GsGZFile
{
public:
	GsGZFile(const char* gzfile);
	~GsGZFile();

};

UTILITY_ENDNS