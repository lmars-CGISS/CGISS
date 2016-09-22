// polynomial.h: interface for the polynomial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYNOMIAL_H__FBAF093F_0B9E_4173_9BB6_8D2ABD029203__INCLUDED_)
#define AFX_POLYNOMIAL_H__FBAF093F_0B9E_4173_9BB6_8D2ABD029203__INCLUDED_

#include <vector>
#include "geomacro.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

/*
polynomial 用来描述多项式
假如 A是一个polynomial 它们它描述了下面的一个多项式：
   A[0] + A[1]*x + A[2]*x^2 + ……
*/

class GEO_DLL polynomial : public std::vector<double> 
{
public:
    polynomial& stand(double tol=0); //去除等于0的最高项

    polynomial& operator += (const polynomial&);
    polynomial& operator -= (const polynomial&);
    polynomial& operator += (double a);
    polynomial& operator -= (double a){ return operator+= (-a); }
    polynomial& operator *= (double);
    polynomial& operator /= (double a){ return (*this)*=1/a; }

    polynomial operator - (){ return polynomial(*this)*=-1; }
    polynomial operator + (double a)const{ return polynomial(*this)+=a; }
    polynomial operator - (double a)const{ return polynomial(*this)-=a; }
    polynomial operator + (const polynomial &a)const{ return polynomial(*this)+=a; }
    polynomial operator - (const polynomial &a)const{ return polynomial(*this)-=a; }

    polynomial operator * (double a)const{ return polynomial(*this)*=a; }
    polynomial operator / (double a)const{ return polynomial(*this)/=a; }
    
    polynomial operator * (const polynomial&)const;

    polynomial operator / (polynomial)const;
    polynomial operator % (polynomial)const;
    
    double operator()(double x)const;

    polynomial operator()(polynomial a)const; //复合函数

    //描述：得到复合函数me(x+a)
    polynomial& offset(double a);

    //描述：得到复合函数me(a*x)
    polynomial& power(double a);
    
    //描述：得到导函数
    polynomial diffrence ()const;
    
    //描述：得到积分函数
    polynomial integral ()const;

    //描述：计算方程的根(函数不会删除x中原有的数据)
    int root(std::vector<double> &x)const;

    double minimum(double &t)const;

    //描述：得到函数在区间[a,b]的最大最小值，并且将它们扩充到_min,_max
    void minmax(double a,double b,double &_min,double &_max)const;
};

//描述：返回组合数C(m,n)也就是m!*(n-m)!/n!
GEO_DLL double comb_num(int m,int n);

GEO_NAMESPACE_END

#endif // !defined(AFX_POLYNOMIAL_H__FBAF093F_0B9E_4173_9BB6_8D2ABD029203__INCLUDED_)
