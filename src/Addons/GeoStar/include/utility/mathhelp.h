 #pragma once
#include "preconfig.h" 
#include <climits>
#include <stdlib.h>

//geomathd 去掉后很多宏定义和函数找不到 引用添加到此处
#include <float.h>
#include <math.h>
UTILITY_NS  
	
/// \brief 数学相关的函数
class GS_API GsMath
{
public:
	template<class T>
	static T Random(T min,T max)
	{
		int n  = rand();
		return min + n * 1.0 * (max - min)/ INT_MAX ;
	}
	template<class U,class V>
	static double Max(U a,V b)
	{
		return a >b?a:b;
	}
	template<class U,class V>
	static double Min(U a,V b)
	{
		return a <b?a:b;
	}
	/// \brief 判断两个double是否相等
	static bool IsEqual(double d1,double d2);

	/// \brief 判断两个float是否相等
	static bool IsEqual(float f1,float f2);
	
	/// \brief 四舍五入到最邻近的整数
	static double Round(double r);

	/// \brief 四舍五入到最邻近的整数
	static float Round(float r);

	/// \brief 度转换为弧度
	static double ToRadian(double degree);
	/// \brief 弧度转换为度
	static double ToDegree(double radian);

	/// \brief 无效double
	static double NaN();

	/// \brief 获取圆周率PI
	static double Pi();

};
UTILITY_ENDNS