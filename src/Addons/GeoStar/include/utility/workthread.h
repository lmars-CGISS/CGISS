#pragma once
#include "preconfig.h" 
#include <list>
#include "locker.h"
UTILITY_NS
/// \brief 工作线程，通过继承工作线程类，实现类对多线程的支持
class GS_API GsWorkThread
{
protected:
	void* m_pThread;
public:
	GsWorkThread();
	virtual ~GsWorkThread();
	
	/// \brief 启动线程
    ///\return 返回执行是否成功
	virtual bool StartThread();

	/// \brief 实现是否在执行
    ///\return 返回实现是否在执行
	virtual bool IsWorking();

	/// \brief 发送关闭线程的通知，或等待线程结束
   /// \brief bWaitFinish是否等待线程结束
   ///\return 返回是否成功
	virtual bool Shutdown(bool bWaitFinish = true);

	
	/// \brief 获取线程的ID
    ///\return 返回线程的ID
	virtual int ThreadID();

	/// \brief 是否需要停止，在Execute函数中判断线程是否接受到了外部的停止通知
	/// \brief 调用Shutdown方法后ShouldStop会返回true
    ///\return 如果线程可以结束了则返回true
	virtual bool ShouldStop();

	/// \brief 发送关闭线程的通知后等待线程结束
    ///\return 返回是否成功
	virtual bool Wait();

	/// \brief 执行线程，实现此纯虚函数
    ///\return 返回执行是否成功
	virtual bool Execute() = 0;

};



/// \brief 线程池参数
class GS_API GsThreadPoolParameter
{
public:
	GsThreadPoolParameter();
	virtual ~GsThreadPoolParameter();
};

/// \brief 线程工人，在线程池中工作的工人，继承此类实现工作线程线程上工作的工人
class GS_API GsThreadWorker
{
public:
	GsThreadWorker();
	virtual ~GsThreadWorker();
	
	/// \brief 初始化线程池工人。
    /// \brief pParameter线程池的参数
    ///\return 返回是否初始化成功
	virtual bool Initialize(GsThreadPoolParameter* pParameter)  = 0;

	/// \brief 执行线程
    /// \brief pParameter线程池的参数
    ///\return 返回执行是否成功
	virtual bool Execute(GsThreadPoolParameter* pParameter)  = 0;


	/// \brief 执行线程
    /// \brief pParameter线程池的参数
    ///\return 返回执行是否成功
	virtual bool Terminate(GsThreadPoolParameter* pParameter)  = 0;

};

/// \brief 线程池。继承此类实现CreateWorker函数，实现自定义的线程池
class GS_API GsThreadPool:public GsLock
{
	std::list<GsThreadWorker*> m_lstWorker;
	void* m_pThreadPool;
protected:
	
	/// \brief 创建一个线程此工人对象
    /// \brief pParameter线程池的参数
    ///\return 线程池工人对象指针
	virtual GsThreadWorker* CreateWorker(GsThreadPoolParameter* pParameter =  NULL) =  0;

	GsThreadPoolParameter* m_pParameter;
public:
	GsThreadPool();
	virtual ~GsThreadPool();

	virtual GsThreadWorker* GetWorker(GsThreadPoolParameter* pParameter =  NULL);
	virtual void RecoveryWorker(GsThreadWorker* worker);

	
	/// \brief 初始化线程池
    /// \brief pParameter线程池的参数
    /// \brief nMinThread线程池的最少线程数量
    /// \brief nMaxThread线程池的最大线程数量
    ///\return 返回执行是否成功
	virtual bool Initialize(GsThreadPoolParameter* pParameter,int nMinThread,int nMaxThread);

	/// \brief 出发一个线程工作。
    /// \brief pParameter线程池的参数，如果为空则缺省系统初始化线程池的参数
    ///\return 返回执行是否成功
	virtual bool Trigger(GsThreadPoolParameter* pParameter = 0);


	/// \brief 关闭线程池
    ///\return 返回执行是否成功
	virtual bool Shutdown();

};
UTILITY_ENDNS