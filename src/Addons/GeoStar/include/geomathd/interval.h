// interval.h: interface for the interval class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERVAL_H__C5C95236_767B_49DD_88DD_897CB4B1CBD1__INCLUDED_)
#define AFX_INTERVAL_H__C5C95236_767B_49DD_88DD_897CB4B1CBD1__INCLUDED_

#include "geomacro.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

struct GEO_DLL interval : std::vector<double>
{
	interval(){
	}

	interval(double star,double end);

	//描述：加入一个区间[star,end)，要求end>star
	interval& add(double star,double end);

	//描述：减去一个区间[star,end)，要求end>star
	interval& sub(double star,double end);

	//描述：排序this中的各个区间，将其变成合法的状态
	interval& sort();

	//描述：计算两个区间套的并
	interval	operator | (const interval &a)const;

	//描述：计算两个区间套的交
	interval	operator & (const interval &a)const;

	//描述：计算两个区间套的差
	interval	operator - (const interval &a)const;
	
	//描述：是否包含点v
	bool is_cover(double v)const;

	//描述：是否包含区间[star,end)
	bool is_cover(double star,double end)const;

	//描述：是否包含区间套
	bool is_cover(const interval &I)const;

	//描述：是否和区间[star,end)相交
	bool is_intersect(double star,double end)const;

	//描述：是否和区间套相交
	bool is_intersect(const interval &I)const;

	double length()const;

	bool operator > (const interval &a)const{ return is_cover(a); }
	bool operator < (const interval &a)const{ return a.is_cover(*this); }
	bool operator && (const interval &a)const{ return is_intersect(a); }

	bool operator >= (const interval &a)const{
		return *this==a || *this>a;
	}
	bool operator <= (const interval &a)const{
		return *this==a || *this<a;
	}
};

GEO_NAMESPACE_END


#endif // !defined(AFX_INTERVAL_H__C5C95236_767B_49DD_88DD_897CB4B1CBD1__INCLUDED_)
