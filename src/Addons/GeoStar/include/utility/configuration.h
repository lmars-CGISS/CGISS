#pragma once
#include "preconfig.h"
#include "tinyxml2.h"
#include <stringhelp.h>
#include <vectorhelp.h>
#include <memory>
#include <locker.h>

UTILITY_NS

/// \brief 配置类，实现配置的读取和写入。
class GS_API GsConfig
{
	/// \brief Document只有根配置才不为空。
	mutable tinyxml2::XMLDocument* m_pDoc; 
	
	/// \brief 配置的xml节点。
	tinyxml2::XMLElement* m_pEle;
	
	
	/// \brief 如果数据变化则调用此函数设置标识。
	void Dirty();
	
	/// \brief 内部私有函数
	/// \brief 替代字符串中的一部分为新的部分
	void replacestring(GsString& str,const GsString& strFind,const GsString &strReplace)const;
	
	/// \brief 构造路径
	GsString buildpath(tinyxml2::XMLNode* vNode)const;
	
	/// \brief 分割字符串
	void split(const GsString& s, const GsString& delim,GsVector< GsString >& ret)  const;
	
	/// \brief 找寻指定名称的Node
	tinyxml2::XMLElement* findnamenode(tinyxml2::XMLElement* pEle,const char* strName)const;
	
	/// \brief 替代xml中的转义
	void normalstring( GsString& str)const;
	
	/// \brief 深度clone
	tinyxml2::XMLNode* copyto(tinyxml2::XMLNode* pNode,tinyxml2::XMLDocument* doc)const;
	
	
	/// \brief 特殊构造空的配置
	GsConfig(int i);	

public: 
	
	/// \brief 缺省构造，构造一个空的配置
	GsConfig();	
	/// \brief 拷贝构造函数
    GsConfig(const GsConfig & GsConfig) ; 
	/// \brief  pEle配置项目的xml节点
	GsConfig(tinyxml2::XMLElement* pEle); 
	/// \brief 从xml文件或者字符串打开配置
    /// \brief strXML字符串或者配置文件路径
	/// \brief bIsString判断strXML是xml字符串还是文件名，true表示strXML为纯的xml字符串
	GsConfig(const char* strXML,bool bIsString = false);

	/// \brief 等号赋值操作符。 
    /// \brief GsConfig其他配置项  
	GsConfig & operator =(const GsConfig &GsConfig);
	
	/// \brief 析构函数
	virtual ~GsConfig(void);
	 
	/// \brief 获取配置文件的文件名
    /// \brief GsConfig其他配置项	
	GsString FileName() const;
	
	/// \brief 保存到文件中
	bool Save(const char* strFile);
	
	/// \brief 保存为XML字符串
	GsString Save();
	
	/// \brief 判断配置是否发生了变化
	bool IsDirty() const;
	
	/// \brief 获取根配置对象
	GsConfig  Root() const ;
	
	/// \brief 是否为根配置
	bool IsRoot() const;
	
	/// \brief 获取父亲配置对象
	GsConfig Parent() const;
	
	/// \brief 获取设置配置的名称
	GsString Name()const;
	void Name(const GsString& str);
	void Name(const char* str);
	
	/// \brief 获取设置配置项的描述
	GsString Description()const;
	void Description(const GsString& str);
	void Description(const char* str);

	/// \brief 配置的数据类型。
	GsString Type()const;
	void Type(const GsString& str);
	void Type(const char* str);
	
	/// \brief 判断配置是否有效
	bool IsValid()const;
	bool Good() const;
	bool IsNull() const;
	
	/// \brief 获取配置的路径
	GsString Path()const;
	
	/// \brief 选择一个子的配置，如果不存在的话会创建这个子的配置并返回。
	GsConfig Child(const char* strName);
	GsConfig Child(const GsString& strName);

	/// \brief 是否存在某个子的配置
	bool Exist(const char* strName)const;
	bool Exist(const GsString& strName)const;
	
	/// \brief 是否存在子的配置
	bool HasChildren()const;
	/// \brief 是否为同一配置节点
	bool operator ==(const GsConfig& config);

	/// \brief 所有的子对象列表
	GsVector<GsConfig> Children() const;
	void Children(GsVector<GsConfig> &vec) const;

	/// \brief 子配置的名称
	GsVector<GsString> ChildrenName()const;
	void ChildrenName(GsVector<GsString> &vec)const;
	
	/// \brief 选择一个子的配置，如果不存在的话并不会创建
	GsConfig Peek(const char* strName)const;
	GsConfig Peek(const GsString& strName)const;
	
	/// \brief 方括号操作符，设计调用Peek方法。
	GsConfig operator [](const char* strName) const;
	GsConfig operator [](const GsString& strName) const; 

	/// \brief 配置的值
	GsString Value() const;
	/// \brief 设置配置的值
	void Value(const char* strValue) ;
	void Value(const GsString&  strValue) ;
	void Value(int value) ;
	void Value(unsigned int value) ;
	void Value(long long value) ;
	void Value(unsigned long long value) ;
	
	void Value(bool value) ;
	
	void Value(float value) ;
	void Value(double value) ;

	/// \brief 获取字符串值，不存在则返回缺省值
	GsString StringValue(const char* strDefaultValue) const;
	GsString StringValue(const GsString& strDefaultValue) const;
	
	/// \brief 判断是否为特定值类型
	bool IsNumberValue() const;
	bool IsIntValue() const;
	bool IsFloatValue() const;
	bool IsBooleanValue() const;
	
	/// \brief 获取特定类型的值
	int IntValue(int nValue) const;
	long long Int64Value(long long nValue) const;
	bool BoolValue(bool bValue) const;
	double FloatValue(double bFloat) const;

	/// \brief 将另外的分支添加到这个GsConfig中
	void Append(const GsConfig& config);

	/// \brief 清空所有的子配置
	void Clear();
	
	/// \brief 删除一个子配置
	void Remove(const char* childName);
	/// \brief 删除一个子配置
	void Remove(const GsString&  childName);
	

	/// \brief 获取配置的xml节点
	tinyxml2::XMLElement* Element()const{return m_pEle;}

};

/// \brief 全局配置类
class GS_API GsGlobeConfig
{
public:
	/// \brief 全局的配置类根对象。
	static GsSafeObject<GsConfig>& Instance();
	
	/// \brief 将全局的配置保存为文件
	static bool Save(const char* strFile);

	/// \brief 将全局的配置保存为字符串
	static GsString Save();

	/// \brief 从xml或者配置中load配置信息
	static bool Load(const char* strFileOrXML ,bool bFile = true);
};

UTILITY_ENDNS