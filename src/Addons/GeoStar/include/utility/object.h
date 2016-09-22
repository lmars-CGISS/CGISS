 #pragma once
#include "preconfig.h" 
#include <map>
#include <string>
UTILITY_NS
	 

/// \brief 不可拷贝对象，通过继承此类实现对象的不可拷贝
class GS_API GsNoneCopyable
{ 
public:
	GsNoneCopyable() {}

private:
    GsNoneCopyable(const GsNoneCopyable&);
	/// \brief 操作符重载，返回对象的引用
    GsNoneCopyable& operator=(const GsNoneCopyable&);
}; 


/// \brief 引用对象，通过继承此类实现对象对引用计数的支持。
class GS_API GsRefObject:private GsNoneCopyable
{
protected:
	volatile int m_nRefCount;
	/// \brief 当引用计数为0的时候会激发此函数，继承类可以覆盖此函数做特殊的实现
    ///\return 返回false则GsRefObject不会主动删除对象
	virtual bool OnFinalRelease();
public:
	GsRefObject();
	virtual ~GsRefObject();
	
	/// \brief 增加一个引用计数
    ///\return 返回增加后的引用计数值
	virtual int AddRef();
	/// \brief 减少一个引用计数
    ///\return 返回减少后的引用计数值
	virtual int Release();
	/// \brief 获取引用计数的值
    ///\return 返回当前引用计数的值
	virtual int RefCount();
};
 

/// \brief 智能指针模板对象，实现对GsRefObject对象的引用计数自动管理
template <class T>
class GsSmarterPtr
{
public:
	/// \brief 无参构造函数
	GsSmarterPtr() throw()
	{
		p = NULL;
	}
	/// \brief int参数类型构造函数
	GsSmarterPtr(int nNull) throw()
	{  
		p = NULL;
	}
	/// \brief long int参数类型构造函数
	GsSmarterPtr(long int nNull) throw()
	{  
		p = NULL;
	}
	/// \brief 模板构造函数，实现引用计数加1
	template<class O>
	GsSmarterPtr(O* lp,bool bAddRef = true) throw()
	{
		p = dynamic_cast<T*>(lp); // 类型转换
		if (p != NULL && bAddRef)
			p->AddRef(); // 引用计数加1
	}
	/// \brief 模板构造函数，实现引用计数加1
	template<class O>
	GsSmarterPtr(const GsSmarterPtr<O>& lp) throw()
	{
		p = dynamic_cast<T*>(lp.p); // 类型转换
		if (p != NULL)
			p->AddRef(); // 引用计数加1
	}
	/// \brief 构造函数，实现引用计数加1
	GsSmarterPtr(const GsSmarterPtr<T>& lp) throw()
	{
		p = lp.p;
		if (p != NULL)
			p->AddRef(); // 引用计数加1
	}
	/// \brief 构造函数，实现引用计数加1
	GsSmarterPtr(const GsRefObject* lp,bool bAddRef = true) throw()
	{
		p = dynamic_cast<T*>(lp); // 类型转换
		if (p != NULL && bAddRef)
			p->AddRef(); // 引用计数加1
	}
	/// \brief 不能被隐式调用的构造函数，实现引用计数加1
	explicit GsSmarterPtr(T* lp,bool bAddRef = true) throw()
	{
		p = lp;
		if (p != NULL && bAddRef)
			p->AddRef(); // 引用计数加1
	}

public: 
	/// \brief 析构函数，实现引用计数减1
	~GsSmarterPtr() throw()
	{
		if (p)
			p->Release(); // 引用计数减1
	}
	/// \brief 如果指针为空，就转换指针类型
	template<class Q>
	GsSmarterPtr<Q> As()
	{
		if(!p)
			return 0;
		return dynamic_cast<Q*>(p);
	}
	/// \brief 如果指针为空，就转换指针类型
	template<class Q>
	bool Is()
	{
		if(!p)
			return false;
		return dynamic_cast<Q*>(p) != 0;
	}
	/// \brief 类型转化模板
	operator T*() const throw()
	{
		return p;
	}
	/// \brief 类型转化
	operator GsRefObject*() const throw()
	{
		return p;
	}
	/// \brief 类型转化
	operator bool() const throw()
	{
		return 0 != p;
	}
	/// \brief 符号重载
	T& operator*() const
	{ 
		return *p;
	} 
	/// \brief 符号重载
	T** operator&() throw()
	{ 
		return &p;
	}
	/// \brief 符号重载
	T* operator->() const throw()
	{
		return p;
	}
	/// \brief 符号重载
	bool operator!() const throw()
	{
		return (p == 0);
	}
	/// \brief 符号重载
	bool operator<(T* pT) const throw()
	{
		return p < pT;
	}
	/// \brief 符号重载
	bool operator!=(T* pT) const
	{
		return !operator==(pT);
	}
	/// \brief 符号重载
	bool operator==(T* pT) const throw()
	{
		return p == pT;
	}

	/// \brief 引用计数加1
	void AddRef()throw()
	{
		if(p)
          p->AddRef();
		
	}
	/// \brief 引用计数减1
	void Release() throw()
	{
		T* pTemp = p;
		if (pTemp)
		{
			p = NULL;
			pTemp->Release();
		}
	} 
	/// \brief 比较2个指针的值
	bool IsEqualObject(GsRefObject* pOther) throw()
	{
		/// \brief 如果2个object都为null，则返回true
		if (p == NULL && pOther == NULL)
			return true;	
		/// \brief 如果1个object为null，另一个不为null，则返回false
		if (p == NULL || pOther == NULL)
			return false;	
		/// \brief 如果2个object都不为null，则判断他们的值是否相等
		GsRefObject* p1 = dynamic_cast<GsRefObject*>(p);
		return p1 == pOther;
	} 
	/// \brief 引用计数减1
	void Attach(T* p2) throw()
	{
		if (p)
			p->Release();
		p = p2;
	} 
	/// \brief 传递指针的值
	T* Detach() throw()
	{
		T* pt = p;
		p = NULL;
		return pt;
	}
	/// \brief 引用计数加1
	bool CopyTo(T** ppT) throw()
	{
		if (ppT == NULL)
			return false;
		*ppT = p;
		if (p)
			p->AddRef();
		return true;
	}
	 
	
		/// \brief 符号重载，若指针非空，则引用计数加1，否则减1
	T* operator=(T* lp) throw()
	{
		if(p != NULL)
			if(*this == lp)
				return *this;
		if(lp)
			lp->AddRef();
		Attach(lp);
        return *this;
	}
	/// \brief 符号重载，若指针非空，则引用计数加1，否则减1
	T* operator=(const GsSmarterPtr<T>& lp) throw()
	{
        if(*this!=lp)
        {
			if(lp)
				lp->AddRef();
			Attach(lp);
		}
        return *this;
	}

	T* p;
}; 

#define GS_SMARTER_PTR(P) typedef UTILITY_NAME::GsSmarterPtr<P> P ## Ptr
/// \brief GsRefObjectPtr
//GS_SMARTER_PTR(GsRefObject);


/// \brief 类工厂，用于注册类创建函数和创建类。
class GS_API GsClassFactory
{
public:
	typedef GsRefObject* (*FactoryCreate_PTR)();

	/// \brief 注册类创建函数
	static void RegisterFactoryCreate(FactoryCreate_PTR fc_ptr,const char* className);
	
	/// \brief 创建类的实例
	static GsRefObject* CreateInstance(const char* className);
};

#define DECLARE_CLASS_CREATE(class_name) namespace Factory{static UTILITY_NAME::GsRefObject*  CreateClass## class_name (){return new class_name;}}
#define REG_CLASS_CREATE(class_name) UTILITY_NAME::GsClassFactory::RegisterFactoryCreate(Factory::CreateClass## class_name, #class_name);
#define REG_CLASS_CREATE_NS(class_name,NS) UTILITY_NAME::GsClassFactory::RegisterFactoryCreate(NS::Factory::CreateClass## class_name, #class_name);
#define REG_CLASS_CREATE_ALIAS(class_name,alias_name) UTILITY_NAME::GsClassFactory::RegisterFactoryCreate(Factory::CreateClass## class_name, alias_name);


UTILITY_ENDNS
