#pragma once
#include "preconfig.h" 
 
UTILITY_NS 


/// \brief 线程锁
class GS_API  GsLock
{
	void* m_pMutex;
public:
	GsLock();
	virtual ~GsLock();
	
	/// \brief 锁定对象
	virtual void Lock(); 

	/// \brief 释放锁定
	virtual void Unlock();
};

/// \brief 读写线程锁
class GS_API  GsRWLock
{
	void* m_pRWLock;
public:
	GsRWLock();
	virtual ~GsRWLock();

	/// \brief 写锁定对象
	virtual void Lock();
	
	/// \brief 释放写锁定
	virtual void Unlock();


	/// \brief 读锁定对象
	virtual void ReadLock(); 

	/// \brief 释放读锁定
	virtual void ReadUnlock();
};

/// \brief 信号
class GS_API GsSignaler
{
	void* m_pMutex;
	void* m_pSingaler;

public:
	GsSignaler();
	virtual ~GsSignaler(); 

	/// \brief 设置信号
	virtual void Signal();
	 
	/// \brief 等待信号
	virtual void Wait();

	/// \brief 等待信号或者超时
	///\return 返回false则表示超时
	virtual bool Wait(unsigned int milliseconds);

};

/// \brief 自动加锁的对象
class GS_API GsAutoLocker
{
	GsRWLock* m_RW;
	GsLock* m_L;
	bool m_bRead;
public:
	/// \brief 缺省构造函数
	GsAutoLocker(GsLock* L);
	/// \brief 构造函数重载
	GsAutoLocker(GsRWLock* l,bool bReadLock = false);
	/// \brief 构造函数重载
	GsAutoLocker(GsLock& L);
	/// \brief 构造函数重载
	GsAutoLocker(GsRWLock& l,bool bReadLock = false);

	virtual ~GsAutoLocker();

	/// \brief 释放锁定
	void Unlock();

};


/// \brief 锁定对象
#define GS_LOCK_IT(P)  UTILITY_NAME::GsAutoLocker _L(P);

/// \brief 读锁定对象
#define GS_RLOCK_IT(P)  UTILITY_NAME::GsAutoLocker _L(P,true);

/// \brief 锁定自身
#define GS_LOCK_THIS  UTILITY_NAME::GsAutoLocker _L(this);

/// \brief 读锁定自身
#define GS_RLOCK_THIS  UTILITY_NAME::GsAutoLocker _L(this,true);

/// \brief 安全对象，组合锁对象形成安全的对象
template<class T,class L=GsRWLock>
class GsSafeObject:public T,public L
{
};
/// \brief 安全类型，组合锁对象形成安全的类型，适用于轻量的对象
template<class T,class L=GsRWLock>
class GsSafeType:public L
{
public:
	T Value;
};

UTILITY_ENDNS