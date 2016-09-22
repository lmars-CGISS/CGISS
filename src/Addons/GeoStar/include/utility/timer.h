#pragma once
#include "preconfig.h"  
UTILITY_NS
/// \brief 高精度计时器
class GS_API GsStopWatch
{
	volatile double   m_dblFrequency;
	volatile long long m_nLowPart;
	volatile long long m_nHighPart;
public:
	/// \brief 构造
	GsStopWatch(bool bStart = false);
	virtual ~GsStopWatch();

	/// \brief 计时器是否已经开始工作了
	bool IsStarted();

	/// \brief 启动计时器
	bool Start();

	/// \brief 经过的时间（单位秒）
	double EscapedSecond();
	 
	/// \brief 经过的时间（单位毫秒）
	double EscapedMillisecond();

	/// \brief 经过的时间（单位纳秒）
	double EscapedNanosecond();


};


UTILITY_ENDNS
