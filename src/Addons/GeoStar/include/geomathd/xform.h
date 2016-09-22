// xform.h: interface for the xform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XFORM_H__6EE6E435_C25E_41D0_8631_A2A5F0235AA2__INCLUDED_)
#define AFX_XFORM_H__6EE6E435_C25E_41D0_8631_A2A5F0235AA2__INCLUDED_

#include "point.h"
#include<algorithm>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

class path;

/*
| M11 M12 0 |
V = | M21 M22 0 |
| Dx  Dy  1 |

  pt = | x,y,1 |
  
	V(pt) = pt*V
	
*/

struct GEO_DLL  xform
{
	double M11,M12,M21,M22,Dx,Dy;
    xform():M11(1),M22(1),M12(0),M21(0),Dx(0),Dy(0){}
	
    void operator()(double &x,double &y)const
    {
		double a = M11*x+M21*y+Dx;
		y = M12*x+M22*y+Dy;
		x = a;
	}
	
    void operator()(point &pt)const
    {
        operator()(pt.x,pt.y);
    }
    void operator()(point in,point &out)const
    {
		out.x = M11*in.x+M21*in.y+Dx;
		out.y = M12*in.x+M22*in.y+Dy;
	}
	void operator()(std::vector<pnode> &A)const
    {
		std::for_each(A.begin(),A.end(),*this);
	}
    template<class type> void operator()(std::vector<type> &A)const
    {
		std::for_each(A.begin(),A.end(),*this);
	}
	
	template<class type1,class type2>
		void operator()(const std::vector<type1> &in,std::vector<type2> &out)const
    {
		out.resize( in.size() );
		for(int i=in.size(); --i>=0;)
			(*this)(in[i],out[i]);
	}
	
    void operator()(path* L)const;
    void operator()(path& L)const{ operator()(&L); }
	
    
    xform& operator*=(double v)
    {
        M11*=v; M12*=v; Dx*=v;
        M21*=v; M22*=v; Dy*=v;
        return *this;
    }
	
    xform operator*(double v)const
    {
        return xform(*this)*=v;
    }
	
    xform& operator/=(double v)
    {
        if( v==0 ) return *this;
        return (*this)*=(1.0/v);
    }
	
    xform operator/(double v)const
    {
        return xform(*this)/=v;
    }
	
    xform& operator+=(const xform &a)
    {
        M11+=a.M11; M12+=a.M12; Dx+=a.Dx;
        M21+=a.M21; M22+=a.M22; Dy+=a.Dy;
        return *this;
    }
	
    xform operator+(const xform &a)const
    {
        return xform(*this) += a;
    }
	
    xform operator-()const
    {
        return xform(*this) *= -1;
    }
	
    xform& operator-=(const xform &a)
    {
        M11-=a.M11; M12-=a.M12; Dx-=a.Dx;
        M21-=a.M21; M22-=a.M22; Dy-=a.Dy;
        return *this;
    }
	
    xform operator-(const xform &a)const
    {
        return xform(*this) -= a;
    }
	
    bool inverse(xform &out)const
    {
        out.M11 = M22;
        out.M12 = -M12;
        out.M21 = -M21;
        out.M22 = M11;
        out.Dx = M21*Dy-M22*Dx;
        out.Dy = M12*Dx-M11*Dy;
        double D = M11*M22-M12*M21;
        out /= D;
        return D!=0;
    }
	
    xform inverse()const
    {
        xform out;
        inverse(out);
        return out;
    }
	
    xform operator*(const xform &a)const
    {
        xform b;
        b.M11 = M11*a.M11+M12*a.M21;
        b.M12 = M11*a.M12+M12*a.M22;
        b.Dx = Dx*a.M11+Dy*a.M21+a.Dx;
		
        b.M21 = M21*a.M11+M22*a.M21;
        b.M22 = M21*a.M12+M22*a.M22;
        b.Dy = Dx*a.M12+Dy*a.M22+a.Dy;
		
        return b;
    }
	
    xform& operator*=(const xform &a)
    {
        return *this = operator*(a);
    }
	
    xform operator/(const xform &a)const
    {
        return operator*(a.inverse());
    }
	
    xform& operator/=(const xform &a)
    {
        return *this = operator/(a);
    }
	
    xform& offset(double x,double y)
    {
        Dx+=x; Dy+=y; return *this;
    }
};

GEO_NAMESPACE_END

#endif // !defined(AFX_XFORM_H__6EE6E435_C25E_41D0_8631_A2A5F0235AA2__INCLUDED_)
