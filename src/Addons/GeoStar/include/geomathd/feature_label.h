// feature_label.h: interface for the feature_label class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATURE_LABEL_H__390E5D05_5094_4683_8FDA_5EED8EBF519D__INCLUDED_)
#define AFX_FEATURE_LABEL_H__390E5D05_5094_4683_8FDA_5EED8EBF519D__INCLUDED_

#include "path.h"
#include <map>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

GEO_NAMESPACE_BEGIN

/******************** 实现地物的自动标注 ********************
使用方法：
    自动标注的时候主要有两个技术点需要考虑，一个是仅仅只有单个地物的时候如何标注
    另一个是有多个地物的时候如何避让使其互相之间不压盖。

    在feature_label类中第一个技术点由get_single_label函数实现，这个函数根据地物的形状，
    和标注的大小得到若干个候选的标注方案，程序在内部根据美观程度将标注方案由优到劣排好，如果仅仅只标注一个地物，简单的选择第一方案即可

    如果要标注多个地物，就需要创建一个feature_label对象
    利用add_feature函数将每个地物的候选标注方案加入进来，当所有的feature都加入进来之后再调用auto_label函数
    这个函数将对每个地物的候选方案进行组合选择，找到互相之间压盖最少的标注方案，然后就可以调用get_label的到每个地物的标注方案了
************************************************************/

class GEO_DLL feature_label  
{
    struct feature;
    struct label;
    struct label_env;
    struct relation
    {
        relation*   m_next;
        label*      m_friend;
        double      m_value;
    };
    struct label
    {
        feature*    m_feat;
        label*      m_next;
        relation*   m_rel;
        envelope    m_env;

        //得到c和this的压盖面积
        double      rel(label* c);

        //得到自己被压盖的面积
        double      area(bool fix); 

        //删除自身(也就是删除所以朋友label中和自己的关系)
        void        remove(); 
    };
    struct feature
    {
        int         m_id;
        int         m_fixed;
        label*      m_select;
        label*      m_first;

        //调整候选方案得到最少的压盖
        bool adjust(bool fix); 
    };
    typedef std::map<int,feature*> map_t;
    CHeap*  m_heap_feat;
    CHeap*  m_heap_label;
    CHeap*  m_heap_rel;
    map_t   m_map;

    static inline feature* _feat(map_t::value_type v){ return v.second; }

    void get_relation();
public:
	feature_label();
	~feature_label();

    //功能：添加一个地物
    //参数id: 地物的id,一个id只能在添加一次
    //参数n: 候选标注的个数
    //参数candi:各个候选标注的位置
    bool add_feature(int id,int n,const envelope* candi);

    //功能：整体自动标注
    //说明：在对所有的地物调用add_feature之后就应该调用auto_label函数
    //      这个函数将对每个地物决定一个最佳的候选点，之后用户可以通过get_label函数得到最佳的候选点
    void auto_label();
    
    //功能：得到标注点
    bool get_label(int id,envelope& env);

	//功能：得到标注的压盖面积
	double get_overlap_area(int id);

    //功能：固定某个地物
    //说明：当某个地物的标注位置已经决定之后，应该将此地物的位置固定，这样程序内部
    //      将不会考虑对它位置的调整
    bool fix(int id);

    //功能：对某地物不再标注
    //说明：如果某地物无论如何避让都会被以固定的标注严重压盖，则建议不对此地物标注
    //      并且调用此函数删除此地物的标注方案
    bool remove(int id);

    //功能：避让已固定标注
    //说明：在对某个地物决定其标注之前，最好调用一下avoid_fix函数，
    //      这个函数将会在候选方案中找出不被固定标注压盖的最好的方案
    //返回：被固定标注压盖了的面积
    double avoid_fix(int id);

    //功能：得到单个地物的可选标注
    static void get_single_label(const path* l,double rx,double ry,std::vector<envelope>& A);
};

GEO_NAMESPACE_END

#endif // !defined(AFX_FEATURE_LABEL_H__390E5D05_5094_4683_8FDA_5EED8EBF519D__INCLUDED_)
