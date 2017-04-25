#include "memorymanager.h"
UTILITY_NS

/// \brief ���ܶ���
class GS_API GsEncrypt
{
protected:
	GsEncrypt();
public:
	virtual ~GsEncrypt();
	
	/// \brief �����ݼ��������ByteBuffer��
	virtual int Encrypt(const unsigned char* pOriData,int nLen,GsByteBuffer* pOutput) = 0;
	/// \brief �����ݽ��������ByteBuffer��
	virtual int Decrypt(const unsigned char* pEnData,int nLen,GsByteBuffer* pOutput) = 0;


	/// \brief �����ݼ��������ByteBuffer��.����Base64������ַ���
	virtual GsString Encrypt(const unsigned char* pOriData,int nLen);
	/// \brief �����ܺ����base64�ַ�����ʾ�����ݽ��ܳ���
	virtual int Decrypt(const char* strEncryptBase64,GsByteBuffer* pOutput);

};

/// \brief ����DES�㷨�ļ��ܶ���
class GS_API GsDESEncrypt:public GsEncrypt
{
	GsString m_Password;
public:
	GsDESEncrypt(const char* password);
	~GsDESEncrypt();
	/// \brief �����ݼ��������ByteBuffer��
	virtual int Encrypt(const unsigned char* pOriData,int nLen,GsByteBuffer* pOutput);
	/// \brief �����ݽ��������ByteBuffer��
	virtual int Decrypt(const unsigned char* pEnData,int nLen,GsByteBuffer* pOutput);
};

UTILITY_ENDNS