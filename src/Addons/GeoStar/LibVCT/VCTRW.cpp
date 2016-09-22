#include "StdAfx.h"
#include "VCTRW.h"
#include <map>
#include "EnumParser.h"
#include<iomanip>//头文件要加  
BEGIN_SPECIAL_CASE(VCT_FIELD_TYPE)
	PUSH2(Char,VCT_CHAR);
	PUSH2(Int1,VCT_INT1);
	PUSH2(Int2,VCT_SMALLINT)
	PUSH2(Int4,VCT_INTEGER);
	PUSH2(Int8,VCT_INT8);
	PUSH2(Float,VCT_FLOAT);
	PUSH2(Double,VCT_DOUBLE);
	PUSH2(Date,VCT_DATE);
	PUSH2(Time,VCT_TIME);
	PUSH2(Datetime,VCT_DATETIME);
	PUSH2(Varchar,VCT_VARCHAR);
	PUSH2(Varbin,VCT_VARBIN);
	PUSH2(Boolean,VCT_BOOL);
	PUSH2(Numeric,VCT_NUMERIC);
	PUSH2(Integer,VCT_INTEGER);
	PUSH2(Int,VCT_INTEGER);
	PUSH2(Smallint,VCT_SMALLINT);

END_SPECIAL_CASE(VCT_FIELD_TYPE)

BEGIN_SPECIAL_CASE(VCT_GEOMETRY_TYPE)
	PUSH2(Point,VCT_POINT);
	PUSH2(Line,VCT_LINE);
	PUSH2(Polygon,VCT_POLYGON)
	PUSH2(Solid,VCT_SOLID);
	PUSH2(Annotation,VCT_ANNOTATION); 
	PUSH2(Aggregation,VCT_AGGREGATION); 
	
END_SPECIAL_CASE(VCT_GEOMETRY_TYPE)


#pragma region string help
/// \brief 字符串是否为空或者无效字符串
bool IsNullOrEmpty(const char* str)
{
	return NULL == str || strlen(str) == 0;
}

/// \brief 将字符串分割为若干子串
std::vector<std::string> Split(const std::string& str,const std::string&  sep) 
{
	std::vector<std::string>  ret_;
	if(str.empty())
		return ret_;

	if(sep.empty())
	{
		ret_.push_back(str);
		return ret_;
	}

    std::string tmp;
    std::string::size_type pos_begin = str.find_first_not_of(sep);
    std::string::size_type comma_pos = 0;

    while (pos_begin != std::string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != std::string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return ret_; 
}

std::vector<std::string> Split(const char* str,const char*   sep) 
{
	if(IsNullOrEmpty(str))
		return std::vector<std::string>();
	if(IsNullOrEmpty(sep))
	{
		std::vector<std::string> ret;
		ret.push_back(str);
		return ret;
	}
	return Split(std::string(str),std::string(sep));
	
}

//判断字符串是否以某个字符串结束
bool EndWith(const char* str,const char* tail,int nLen = 0,int nTailLen = 0)
{
	if(NULL == str || NULL == tail)
		return false;
	if(nLen <=0)
		nLen =  strlen(str);
	if(nTailLen <=0)
		nTailLen  = strlen(tail);
	if(nTailLen  > nLen)
		return false;
	str+=(nLen - nTailLen);

	return stricmp(str,tail) == 0;
}
bool EndWith(const std::string& str,const std::string& tail)
{
	return EndWith(str.c_str(),tail.c_str(),str.length(),tail.length());
}
//看字符串是否以某某开头。
bool StartWith(const char* str,const char* head)
{
	return strnicmp(str,head,strlen(head)) == 0;
}
//看字符串是否以某某开头。
bool StartWith(const std::string& str,const std::string& head)
{
	return StartWith(str.c_str(),head.c_str());
}
 

/// \brief 剔除字符串前面空白字符
std::string TrimLeft(const char* str)
{
	if(IsNullOrEmpty(str))
		return std::string();
	std::string ss = str;
	
	
	ss.erase(0, ss.find_first_not_of(" \n\r\t"));   

	return ss;
}

/// \brief 剔除字符串尾部的空白字符
std::string TrimRight(const char* str)
{
	if(IsNullOrEmpty(str))
		return std::string();
	std::string ss = str;
	ss.erase(ss.find_last_not_of(" \n\r\t") + 1);  
	return ss;
}

/// \brief 剔除字符串前面的空白字符
std::string Trim(const char* str)
{
	if(IsNullOrEmpty(str))
		return std::string();
	std::string ss = TrimLeft(str);
	return TrimRight(ss.c_str());
} 


/// \brief 将字符串中的制定字符串替换为新的部分
std::string Replace(const char* ss,const char* src,const char* dst)
{
	if(IsNullOrEmpty(ss))
		return std::string();
	if(IsNullOrEmpty(src))
		return std::string(ss);

	std::string ret;
	std::string str = ss;
	std::string srcc=src;
  	std::string dest;
	if(!IsNullOrEmpty(dst))
		dest = dst;
	
    std::string::size_type pos_begin = 0;
    std::string::size_type pos= str.find(src);
    while (pos != std::string::npos)
    { 
		if(pos==0)
			ret+=dest;
		else{
			ret.append(str,pos_begin,pos-pos_begin);
			ret+=dest;
		}
		pos_begin=pos+srcc.length();
		pos=str.find(src,pos_begin);
    }
    if (pos_begin < str.length())
        ret.append(str.begin() + pos_begin, str.end());
    return ret;
	
}

#pragma endregion
    
VCTParser::VCTParser(const char* vct)
{
	m_strVCTFile = vct;
	m_LineCache.resize(1024*1024);
	m_Separator=",";
	m_pProgress = NULL;
	m_fs.open(m_strVCTFile.c_str());

	m_GeometryIndex.set_empty_key(VCT_GEOMETRY_UNSURPORTED);

	m_AttributeIndex.set_empty_key(std::string());
	m_StyleIndex.set_empty_key(std::string());
	m_RelationTableIndex.set_empty_key(std::string());
	m_VarCharIndex.set_empty_key(-1);
	m_NodeTopoIndex.set_empty_key(-1);
	m_EdgeTopoIndex.set_empty_key(-1);

}
VCTProgress* VCTParser::Progress()
{
	return m_pProgress;
}
void  VCTParser::Progress(VCTProgress* progress)
{
	m_pProgress = progress;
}


VCTParser::~VCTParser(void)
{
}
//文件类型
VCT_FILE_FORMAT VCTParser::FileFormat()
{
	return m_Format;
}
VCTHead& VCTParser::Head()
{
	return m_Head;
}
std::vector<VCTFeatureCode>&  VCTParser::FeatureCodes()
{
	return m_FeatureCodes;
}
std::vector<VCTTableStructure>&  VCTParser::TableStructures()
{
	return m_TableStructures;
}


//读取一行
const char* VCTParser::ReadLine()
{
	m_Pos = m_fs.tellg();
	if(m_pProgress)
		m_pProgress->OnProgress(m_Pos);

	char* pHead = &m_LineCache[0];
	m_fs.getline(pHead,m_LineCache.size());
	m_Line = pHead;
	return pHead;
} 

void VCTParser::ParseHead(const char* strLine)
{
		std::vector<std::string> vecKeys = Split(strLine,":");
		if(vecKeys.size() <2)
			return;

		//从容器获得文件头，直接写入
		VCTHead	&Head = m_Head;

		std::string strKey = Trim(vecKeys.begin()->c_str());
		std::string strValue = Trim(vecKeys.back().c_str());

		if(stricmp(strKey.c_str(),"DataMark")==0)
		{
			Head.strDataMark = strValue;
			if (0 == strnicmp(Head.strDataMark.c_str(),"CNSDTF-VCT",10))
				m_Format = VCT_1999;
			else if (0 == strnicmp(Head.strDataMark.c_str(),"LANDUSE-DAT",11))
				m_Format = VCT_LAND; 
			else if (0 == strnicmp(Head.strDataMark.c_str(),"CADASTRE.VCT",11))
				m_Format = VCT_CADASTRAL;  
			else if (0 == strnicmp(Head.strDataMark.c_str(),"LANDUSE.VCT",11))
				m_Format = VCT_LANDUSE;  
			return;
		}
		if(stricmp(strKey.c_str(),"Version")==0)
		{
			Head.strVersion =  strValue;
			Head.fVersion = atof(strValue.c_str());
			if (VCT_1999 == m_Format)
			{
				if ( 0 == strnicmp( Head.strVersion.c_str(), "GB/T17798-2007", 14))					
				{
					Head.fVersion = 2.0;
					m_Format = VCT_2007;
				}
			} 
			else if (VCT_LAND == m_Format)
			{
				if (0 == strnicmp(Head.strVersion.c_str(), "1.1", 14))
				{
					m_Format = VCT_GD;
				}
			}				

			return;
		}
		if(stricmp(strKey.c_str(),"Unit")==0)
		{
			if (  !strValue.empty())
				Head.chUnit = strValue.front();
			
			return;
		}
		if(stricmp(strKey.c_str(),"Dim")==0)
		{
			Head.nDim = atoi( strValue.c_str() );
			return;
		}

		if(stricmp(strKey.c_str(),"Topo")==0)
		{
			Head.nTopo = atoi( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"CoordSysType")==0)
		{
			if (  !strValue.empty())
				Head.chCoordSysType =  strValue.front();
			return;
		}
		if(stricmp(strKey.c_str(),"Spheroid")==0)
		{
			Head.strSpheroid = strValue;
			return;
		}
		if(stricmp(strKey.c_str(),"Projection")==0)
		{
			Head.strProjection = strValue;
			return;
		}
		if(stricmp(strKey.c_str(),"Parameters")==0)
		{
			Head.strParameters = strValue;
			return;
		}
		if(stricmp(strKey.c_str(),"HorizontalCRS")==0)
		{
			Head.strHorizontalCRS = strValue;
			return;
		}
		if(stricmp(strKey.c_str(),"VerticalDatum")==0)
		{
			Head.strVerticalCRS = strValue;
			return;
		}
		if(stricmp(strKey.c_str(),"TemporalReferenceSystem")==0)
		{
			Head.strTimeRS = strValue;
			return;
		}
		if(stricmp(strKey.c_str(),"ExtentMax")==0)
		{
			std::vector<std::string> vec = Split(strValue,m_Separator);
			if(vec.size() >0) Head.dfMaxX = atof(vec[0].c_str());
			if(vec.size() >1) Head.dfMaxY = atof(vec[1].c_str());
			if(vec.size() >2) Head.dfMaxZ = atof(vec[2].c_str());
			return;
		}
		if(stricmp(strKey.c_str(),"ExtentMin")==0)
		{
			std::vector<std::string> vec = Split(strValue,m_Separator);
			if(vec.size() >0) Head.dfMinX = atof(vec[0].c_str());
			if(vec.size() >1) Head.dfMinY = atof(vec[1].c_str());
			if(vec.size() >2) Head.dfMinZ = atof(vec[2].c_str());
			return;
		}
		if(stricmp(strKey.c_str(),"MinX")==0)
		{
			Head.dfMinX = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"MinY")==0)
		{
			Head.dfMinY = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"MinZ")==0)
		{
			Head.dfMinZ = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"MaxX")==0)
		{
			Head.dfMaxX = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"MaxY")==0)
		{
			Head.dfMaxY = atof( strValue.c_str() );
			return;
		}

		if(stricmp(strKey.c_str(),"MaxZ")==0)
		{
			Head.dfMaxZ = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"ScaleM")==0)
		{
			Head.nScaleM = atol( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"Date")==0)
		{
			Head.strDate = strValue.c_str();
			return;
		}
		if(stricmp(strKey.c_str(),"Separator")==0)
		{
			if(!strValue.empty())
			{
				Head.chSeparator = strValue.front();
				m_Separator = strValue;
			}
			return;
		}

		if(stricmp(strKey.c_str(),"Meridian")==0)
		{
			Head.dMeridian = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"Taren")==0)
		{
			Head.dTaren = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"CoordinateSystemType")==0)
		{
			Head.strCSType = atof( strValue.c_str() );
			return;
		}

		if(stricmp(strKey.c_str(),"XAxisDirection")==0)
		{
			Head.strXAxis = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"YAxisDirection")==0)
		{
			Head.strYAxis = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"XYUnit")==0)
		{
			Head.strXYUnit = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"ZUnit")==0)
		{
			Head.strZUnit = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"PrimeMeridian")==0)
		{
			Head.strPM = atof( strValue.c_str() );
			return;
		}
		if(stricmp(strKey.c_str(),"Offset")==0)
		{
			std::vector<std::string> vec = Split(strValue,m_Separator);
			if(vec.size() >0) Head.dOffsetX = atof(vec[0].c_str());
			if(vec.size() >1) Head.dOffsetY = atof(vec[1].c_str());
			if(vec.size() >2) Head.dOffsetZ = atof(vec[2].c_str());
			return;
		}

}
void VCTParser::ParseFeatureCode(const char* strLine)
{
	std::vector<std::string> vecKeys = Split(strLine,m_Separator);
		
	int i = 0;
	VCTFeatureCode code;
	code.strUserID = vecKeys[i++];
	code.strName = vecKeys[i++];
	code.GeometryType =  CEnumParser::ParserFromString(vecKeys[i++].c_str(),VCT_GEOMETRY_TYPE::VCT_GEOMETRY_UNSURPORTED);
	// 3
	if (m_Format == VCT_1999 || m_Format == VCT_LAND)		
		code.ulColor.Quad = atol(vecKeys[i++].c_str());
	else if (m_Format == VCT_LANDUSE || m_Format == VCT_CADASTRAL)
	{
		code.ulColor.RGBA[0] = atol(vecKeys[i++].c_str());
		code.ulColor.RGBA[1] = atol(vecKeys[i++].c_str());
		code.ulColor.RGBA[2] = atol(vecKeys[i++].c_str());
		code.ulColor.RGBA[3] = 0xFF;
	}
	code.strAttributeTableName = vecKeys[i++].c_str();
	m_FeatureCodes.push_back(code);
}

bool VCTParser::ParseObjectHead(VCTObjectHeader& head)
{
	head.nObjID = _atoi64(CurrentLine());
	if(!ReadToNoneEmpty()) return false;
	
	if (m_Format == VCT_GD)
	{
		head.strStyle = CurrentLine();
		if(!ReadToNoneEmpty()) return false;
		head.strUserID = CurrentLine();
	}
	else
	{
		head.strUserID = CurrentLine();
		if(!ReadToNoneEmpty()) return false;
		head.strStyle = CurrentLine();
	} 
	return true;
}
bool VCTParser::ParsePoint(VCTPoint3D& p)
{
	p.z = 0;
	if(!ReadToNoneEmpty()) return false;
	std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
	if(vec.size() <2)
		return false;
	if(vec.size() >0) p.x = atof(vec[0].c_str());
	if(vec.size() >1) p.y = atof(vec[1].c_str());
	if(vec.size() >2) p.z = atof(vec[2].c_str());
	return true;
}
bool VCTParser::ParsePoint(std::vector<VCTPoint3D>& pt,int nCount)
{
	if(nCount ==0)
	{
		if(!ReadToNoneEmpty()) return false;
		nCount = atoi(CurrentLine());
	}
	if(nCount <=0)
		return false;

	pt.reserve(pt.size() + nCount);
	while(nCount >0)
	{
		if(!ReadToNoneEmpty()) return false;
		std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
		VCTPoint3D p;
		if(vec.size() >0) p.x = atof(vec[0].c_str());
		if(vec.size() >1) p.y = atof(vec[1].c_str());
		if(vec.size() >2) p.z = atof(vec[2].c_str());
		
		pt.push_back(p);
		nCount--;
	}

	return true;
}

void VCTParser::ParseAnnotation()
{
	VCTAnnotation geo;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		geo.vecAnnoPoint.clear(); 

		fpos_t pos = m_Pos;
		if(ParseAnnotation(geo))
			Cache(geo,pos); 
		while(!ReadToEndObject());
	}
}
bool VCTParser::ParseAnnotation(VCTAnnotation& geo)
{	
	geo.ObjHeader.bValid = false;
	if(!ParseObjectHead(geo.ObjHeader)) return false;
	 
	if (m_Format != VCT_2007)
	{
		//<字体><CR><颜色><CR><字型><CR><大小><CR><间隔><CR>
		//<注记内容><CR><注记位置点数><CR>{<X>,<Y>,< ><CR>}
		if (m_Format == VCT_GD)
		{
			ReadToNoneEmpty();
			geo.strText = CurrentLine();
		}
		ReadToNoneEmpty();
		geo.strFontName = CurrentLine();

		ReadToNoneEmpty();
		if (m_Format == VCT_LANDUSE || m_Format == VCT_CADASTRAL)
		{
			std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
			geo.ulColor.Quad = 0;
			if(vec.size() >0) geo.ulColor.RGBA[0] =  atoi(vec[0].c_str());
			if(vec.size() >1) geo.ulColor.RGBA[1] =  atoi(vec[1].c_str());
			if(vec.size() >2) geo.ulColor.RGBA[2] =  atoi(vec[2].c_str()); 
		} 
		else
			geo.ulColor.Quad = atoi(CurrentLine()); 
		
		ReadToNoneEmpty();
		std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
		if(vec.size() >0) geo.nWeight = atoi(vec[0].c_str());
		if(vec.size() >1) geo.nType = atoi(vec[1].c_str());
		geo.bUnderline = false;
		if(vec.size() >2) 
		{
			std::string strUL = vec[2];
			if (strUL == "T" || strUL == "t" || strUL == "Y" || strUL == "y")
				geo.bUnderline = true;
		}

		ReadToNoneEmpty();
		vec = Split(CurrentLine(),m_Separator.c_str());
		if (vec.size() == 2)
		{
			geo.bSizeNumber = false;
			geo.dfTextWidth = atof(vec[0].c_str());
			geo.dfTextHeight = atof(vec[1].c_str());
		}
		else if(vec.size() == 1)
		{
			geo.bSizeNumber = true;
			geo.dfSizeNumber = atof(vec[0].c_str());
		}

		ReadToNoneEmpty();
		geo.dfSpace = atof(CurrentLine());
		if (m_Format != VCT_GD)
		{
			ReadToNoneEmpty();
			geo.strText = CurrentLine();
		}
		ReadToNoneEmpty();
		
		std::vector<VCTPoint3D> vecpt;
		if(!ParsePoint(vecpt))
			return false;
		
		if (vecpt.size() == 1)
			geo.FeatureType = VCT_ANNO_SINGLE;
		else
			geo.FeatureType = VCT_ANNO_MULTIPLE;
		geo.vecAnnoPoint.reserve(vecpt.size());

		std::vector<VCTPoint3D>::iterator it = vecpt.begin();
		for(;it != vecpt.end();it++)
		{
			VCTAnnoPoint p;
			p.vctPoint3D = *it;
			p.vctPoint3D.z  = 0;
			p.fShiftDegree = it->z;
			geo.vecAnnoPoint.push_back(p);
		}
		return true;
	}

	if(!ReadToNoneEmpty()) return false;
	int type = atoi( CurrentLine());
	if(type == 1)
		geo.FeatureType = VCT_ANNO_SINGLE;		
	else if(type == 2)
		geo.FeatureType = VCT_ANNO_MULTIPLE;	

	// 开始读取注记内容
	if(!ReadToNoneEmpty()) return false;
	geo.strText = CurrentLine();
	// 开始读注记点坐标
	
	std::vector<VCTPoint3D> vecpt;
	if ( VCT_ANNO_SINGLE == geo.FeatureType )
		ParsePoint(vecpt,1);
	else
		ParsePoint(vecpt); 

	std::vector<VCTPoint3D>::iterator it = vecpt.begin();
	for(;it != vecpt.end();it++)
	{
		VCTAnnoPoint p;
		p.vctPoint3D = *it;
		p.vctPoint3D.z  = 0;
		p.fShiftDegree = it->z;
		geo.vecAnnoPoint.push_back(p);
	}
	return true;
}
	 

void VCTParser::ParseSolid()
{
	VCTSolid geo;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		geo.vecSolidElement.clear();
		geo.vecSubOid.clear();

		fpos_t pos = m_Pos;
		if(ParseSolid(geo))
			Cache(geo,pos); 
		while(!ReadToEndObject());
	}
}
bool VCTParser::ParseSolid(VCTSolid& geo)
{
	geo.ObjHeader.bValid = false;
	if(!ParseObjectHead(geo.ObjHeader)) return false;
	
	if(!ReadToNoneEmpty()) return false;
	int type = atoi( CurrentLine());

	switch(type) 
	{
	case 1:
		geo.FeatureType = VCT_SOLID_DIRECT;
		break;
			
	case 2:
		geo.FeatureType = VCT_SOLID_INDIRECT;
		break;
	default:
		return false;
	}
	if(!ParsePoint(geo.LabPoibt)) return false;
	if(!ReadToNoneEmpty()) return false;
	int count = atoi( CurrentLine());
	if( VCT_SOLID_DIRECT == geo.FeatureType ) 
	{
		while(count-->0)
		{
			VCTSolidElement ele;
			// 读取直接坐标的体的特征类型
			if(!ReadToNoneEmpty()) return false;
			type = atoi( CurrentLine());
			ele.GeoType = (VCT_SOLID_GEOMETRY_TYPE)VCT_SOLID_ROTATE;
			if(type == 11)
				ParsePoint(ele.vecPoints);
			else if(type == 12)
				ParsePoint(ele.vecPoints);
			else if(type == 13)
			{
				ParsePoint(ele.vecPoints);
				// 读取旋转面     
				std::vector<VCTPolygonElement> temp;
				if(!ParsePolygon(temp)) return false;
				if(temp.empty()) return false;
				ele.PolygonElement = temp.front();
			} 
			else 
				return false;

			geo.vecSolidElement.push_back(ele);
		}
	}
	else
	{

	}

	return true;
}


void VCTParser::ParsePolygon()
{
	VCTPolygon geo;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		geo.vecPolygonElement.clear();
		geo.PolygonIndrect.vecnSubOID.clear();
		fpos_t pos = m_Pos;
		if(ParsePolygon(geo))
			Cache(geo,pos);  
		while(!ReadToEndObject());
	}
}
bool VCTParser::ParsePolygon(std::vector<VCTPolygonElement>& vecEle)
{
	
	//1.0版本
	if (m_Format != VCT_2007)
	{
		VCTPolygonElement ele;
		ele.GeoType = VCT_POLYGON_SIMPLE;
		ParsePoint(ele.vecPoints);
		vecEle.push_back(ele);
		return true;
	}
	//2.0版本
 	if(!ReadToNoneEmpty()) return false;
	int nRingCount = atol(CurrentLine());
	while(nRingCount-- > 0)
	{
		if(!ReadToNoneEmpty()) return false;
		int type = atol(CurrentLine());
		VCTPolygonElement ele;
		ele.GeoType = (VCT_POLYGON_GEOMETRY_TYPE)type;
		if(ele.GeoType == VCT_POLYGON_SIMPLE)
		{
			ParsePoint(ele.vecPoints);
			if(ele.vecPoints.size() <3) return false;
		}
		else if(ele.GeoType == VCT_POLYGON_3POINTCIRCLE)
		{
			ParsePoint(ele.vecPoints);
			if(ele.vecPoints.size() <3) return false;
		}
		else if(ele.GeoType == VCT_POLYGON_CIRCLE)
		{
			ParsePoint(ele.vecPoints,1);
			if(!ReadToNoneEmpty()) return false;
			ele.dfRadius = atof(CurrentLine());
		}
		else if(ele.GeoType == VCT_POLYGON_ELLIPSE)
		{
			ParsePoint(ele.vecPoints,2);
			if(!ReadToNoneEmpty()) return false;
			ele.dfRatio = atof(CurrentLine());
		}
		vecEle.push_back(ele);
	} 
	return true;
}
bool VCTParser::ParsePolygon(VCTPolygon& geo)
{
	geo.ObjHeader.bValid = false;
	if(!ParseObjectHead(geo.ObjHeader)) return false;
	
	 
	if (m_Format != VCT_2007)
	{
		if (m_Head.nTopo == 0)
			geo.FeatureType = VCT_POLYGON_DIRECT;
		else
			geo.FeatureType = VCT_POLYGON_INDIRECT;
	}
	else
	{
		
		if(!ReadToNoneEmpty()) return false;
		int type = atoi( CurrentLine());
		switch( type) 
		{
		case 1:
			geo.FeatureType = VCT_POLYGON_DIRECT;
			break;
				
		case 100:
			geo.FeatureType = VCT_POLYGON_INDIRECT;
			break;

		default:
			return false;
		}
	}
	if(!ParsePoint(geo.LabPoint)) return false;

	//直接坐标
	if(geo.FeatureType == VCT_POLYGON_DIRECT)
	{
		if(!ParsePolygon(geo.vecPolygonElement))
			return false;
	}
	else //间接坐标。
	{
		//1.0版本
		if (m_Format != VCT_2007)
		{
			geo.PolygonIndrect.IndirectType = VCT_POLYGON_INDIRECT_SUB_LINE;
		}
		else
		{
			// 得到间接面的类型
			if(!ReadToNoneEmpty()) return false;
			int type = atoi( CurrentLine() );
			switch(type)
			{
			case 21:
				geo.PolygonIndrect.IndirectType = VCT_POLYGON_INDIRECT_SUB_LINE;
				break;

			case 22:
				geo.PolygonIndrect.IndirectType = VCT_POLYGON_INDIRECT_SUB_POLYGON;
				break;

			default:
				return false;
			}

			ParseRef(geo.PolygonIndrect.vecnSubOID);
		}

	}

	return true;
}
bool VCTParser::ParseRef(std::vector<VCTID>& vecSubOid)
{
	// 得到间接面的类型
	if(!ReadToNoneEmpty()) return false;
	int nLineNum = atoi( CurrentLine() );
	vecSubOid.reserve(nLineNum);
	while(nLineNum > 0)
	{
		if(!ReadToNoneEmpty()) return false;
		std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
		std::vector<std::string>::iterator it = vec.begin();
		for(;it != vec.end();it++)
		{
			vecSubOid.push_back(_atoi64(it->c_str()));
			nLineNum--;
		}
	}
	return true;
}
void VCTParser::ParseLine()
{
	VCTLine ln;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		ln.vecArcID.clear();
		ln.vecLineData.clear();
		fpos_t pos = m_Pos;
		if(ParseLine(ln))
			Cache(ln,pos); 
		while(!ReadToEndObject());
	}
}  
bool VCTParser::ParseLine(VCTLine& geo)
{
	geo.ObjHeader.bValid = false;
	if(!ParseObjectHead(geo.ObjHeader)) return false;
	
	if(!ReadToNoneEmpty()) return false;
	int type = atoi( CurrentLine());	 
	
	if(type >0 && type <7)
		geo.FeatureType = VCT_LINE_DIRECT;
	else  if(type == 100)
		geo.FeatureType = VCT_LINE_INDIRECT;
	else
		return false;
	//直接坐标
	if(geo.FeatureType == VCT_LINE_DIRECT)
	{
		if(m_Format != VCT_2007)
		{
			VCTLineElement ele;
			ele.GeometryType = (VCT_LINE_GEOMETRY_TYPE)type;
			if(!ParsePoint(ele.vecArcPoint))
				return false;
			geo.vecLineData.push_back(ele);
			return true;
		}
		
		if(!ReadToNoneEmpty()) return false;
		int nCount =  atoi( CurrentLine());	
		if(nCount <=0)
			return false;
		for(int i =0;i<nCount;i++)
		{
			VCTLineElement ele;
			if(!ReadToNoneEmpty()) return false;
			type =  atoi( CurrentLine());	
			ele.GeometryType = (VCT_LINE_GEOMETRY_TYPE)type;
			if(!ParsePoint(ele.vecArcPoint))
				return false;
		
			geo.vecLineData.push_back(ele);
		}
		 
	}
	else //间接坐标
		ParseRef(geo.vecArcID); 

	//以下在1.0中有
	if (m_Format  == VCT_1999 && m_Head.nTopo == 2)
	{
		ReadToNoneEmpty();
		geo.nFNode = atoi( CurrentLine() );
		ReadToNoneEmpty();
		geo.nTNode = atoi( CurrentLine() );
		ReadToNoneEmpty();
		geo.nLPolygon = atoi( CurrentLine() );
		ReadToNoneEmpty();
		geo.nRPolygon = atoi( CurrentLine() );
	}
	
	return true;
}


bool VCTParser::ParsePoint(VCTPoint& pt)
{
	pt.ObjHeader.bValid = false;
	if(!ParseObjectHead(pt.ObjHeader)) return false;
	
	if(!ReadToNoneEmpty()) return false;
	int type = atoi( CurrentLine());	
	pt.FeatureType = (VCT_POINT_TYPE)type; 

	switch ( pt.FeatureType)
	{		
	case VCT_POINT_DEFAULT:
	case VCT_POINT_NODE:
		if(!ParsePoint(pt.vecPoint,1))
			return false;
		break;
	case VCT_POINT_DIRECTED:
		if(!ParsePoint(pt.vecPoint,2))
			return false;
		break;
	case VCT_POINT_GROUP:
		if(!ParsePoint(pt.vecPoint))
			return false;
		break;
	}
	//以下在1.0版本中有
	if (m_Format == VCT_1999 && m_Head.nTopo == 2 && type == 2)
		ParseRef(pt.vecLineOID);

	
	return true;
}

void VCTParser::ParsePoint()
{
	VCTPoint pt;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		fpos_t pos = m_Pos;
		pt.vecLineOID.clear();
		pt.vecPoint.clear();
		if(ParsePoint(pt))
			Cache(pt,pos); 

		while(!ReadToEndObject());

	}
}
//读取到对象结尾。
bool VCTParser::ReadToEndObject()
{
	if(!ReadToNoneEmpty())
		return false;
	return stricmp(CurrentLine(),"0") == 0;
}
//读取非空行
bool VCTParser::ReadToNoneEmpty()
{
	if(m_fs.eof())
		return false;

	const char* line = ReadLine();
	//去掉注释段
	if( 0== stricmp(line, "CommentBegin") )
	{
		while(true)
		{
			line = ReadLine();
			if( 0 == strnicmp(line, "CommentEnd",10) ) 
			{
				line = ReadLine();
				break;
			}
		}
	}
	if(strlen(line)>0)
		return true;
	return ReadToNoneEmpty();
}


void VCTParser::ParseTableStructure()
{
	while(!ReadToEndSection())
	{
		const char* strLine = CurrentLine();
		if(IsNullOrEmpty(strLine))
			continue;

		VCTTableStructure tabStruct;
		
		std::vector<std::string> vecKeys = Split(strLine,m_Separator.c_str());
		tabStruct.strTableName = vecKeys.front();
		if(vecKeys.size() >1) tabStruct.vecFields.reserve(atoi(vecKeys[1].c_str()));
		tabStruct.bGeometry = true;
		if(vecKeys.size() >2)
		{
			if (0 == stricmp(vecKeys[2].c_str(),"NoneGeometry"))
				tabStruct.bGeometry = false;
		}
		while(!ReadToEndObject())
		{
			strLine = CurrentLine();
			vecKeys = Split(strLine,m_Separator.c_str());
			VCTField f;
			int i =0;
			f.strFieldName = vecKeys[i++];
			f.FieldType = CEnumParser::ParserFromString(vecKeys[i++].c_str(),VCT_CHAR);
			f.nWidth = 0;
			f.nPrecision = 0;
	
			if(f.FieldType == VCT_CHAR)
				f.nWidth = vecKeys.size()>2?atoi(vecKeys[i++].c_str()):128;
			else  if(f.FieldType == VCT_FLOAT)
			{
				f.nWidth = vecKeys.size()>2?atoi(vecKeys[i++].c_str()):10;
				f.nPrecision = vecKeys.size()>3?atoi(vecKeys[i++].c_str()):8;
			}
			else if(f.FieldType == VCT_DOUBLE)
			{
				f.nWidth = vecKeys.size()>2?atoi(vecKeys[i++].c_str()):38;
				f.nPrecision = vecKeys.size()>3?atoi(vecKeys[i++].c_str()):10;
			}
			tabStruct.vecFields.push_back(f);
		}
		tabStruct.nFieldnum = tabStruct.vecFields.size();
		
		m_TableStructures.push_back(tabStruct);
	}
	
}
/// \brief 解析常量
void VCTParser::ParseConstant()
{
	VCTConstant constval;
	
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
	 
		if(ParseConstant(constval))
			m_ConstantMap[constval.strKey] = constval.strValue;
	}
}
bool VCTParser::ParseConstant(VCTConstant& constpair)
{
	if(!ReadToNoneEmpty()) return false;
	
	std::vector<std::string> vec  = Split(CurrentLine(),m_Separator.c_str());
	constpair.strKey = vec.front();
	constpair.strValue = vec.back();
	return true;
}

/// \brief 关联表
void VCTParser::ParseRelationTable()
{
	VCTRelationTable tab;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		if(ParseRelationTable(tab))
			m_RelationTableIndex[tab.strTableID] = pos;
	}

}
bool VCTParser::ParseRelationTable(VCTRelationTable &tab)
{
	if(!ReadToNoneEmpty()) return false;
	tab.strTableID = CurrentLine();
	if(!ReadToNoneEmpty()) return false;
	//判断0来结束对象
	while(!ReadToEndObject())
	{
		tab.vecRelationPairs.push_back(VCTPairEx());
		VCTPairEx &pair = tab.vecRelationPairs.back();

		pair.strVecAlias = Split(CurrentLine(),m_Separator.c_str());
		if(!pair.strVecAlias.empty())
		{
			pair.strKey = pair.strVecAlias.front();
			pair.strVecAlias.erase(pair.strVecAlias.begin());
		}
		if(!pair.strVecAlias.empty())
		{
			pair.strValue = pair.strVecAlias.front();
			pair.strVecAlias.erase(pair.strVecAlias.begin());
		}
	}
	return true;
}
 
void VCTParser::ParseRepresentation()
{
	VCTStyle style;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		style.vecPairs.clear();
		if(ParseRepresentation(style))
			Cache(style,pos);
	}
}
bool VCTParser::ParseRepresentation(VCTStyle& style)
{ 
	style.strID = CurrentLine();
	if(!ReadToNoneEmpty()) return false;
	int nCount = atoi(CurrentLine());
	while(nCount >0)
	{
		if(!ReadToNoneEmpty()) return false;
		
		style.vecPairs.push_back(VCTPairEx());
		VCTPairEx &VCTPair = style.vecPairs.back();

		VCTPair.strVecAlias = Split(CurrentLine(),m_Separator.c_str());
		if(!VCTPair.strVecAlias.empty())
		{
			VCTPair.strKey = VCTPair.strVecAlias.front();
			VCTPair.strVecAlias.erase(VCTPair.strVecAlias.begin());
		}
		if(!VCTPair.strVecAlias.empty())
		{
			VCTPair.strValue = VCTPair.strVecAlias.front();
			VCTPair.strVecAlias.erase(VCTPair.strVecAlias.begin());
		}
		nCount--;
	}
	ReadToEndObject();
	return true;
}

bool VCTParser::ParseAttribute(VCTAttributeRow& row,int nFieldCount)
{
	std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
	if(vec.empty())
		return false;
	row.nOID = _atoi64(vec.front().c_str());
	row.vecstrFieldValues.clear();
	if(vec.size() <=1)
		return true;
	if(nFieldCount == 0 || vec.size() != nFieldCount)
		row.vecstrFieldValues.insert(row.vecstrFieldValues.begin(),vec.begin()+1,vec.end());
	else
		row.vecstrFieldValues.insert(row.vecstrFieldValues.begin(),vec.begin(),vec.end());

	return true;
}
void  VCTParser::ParseAttribute()
{
	std::string strTableName = CurrentLine();
	if(IsNullOrEmpty(strTableName.c_str()))
		return;

	google::dense_hash_map<VCTID,fpos_t> &cache = m_AttributeIndex[strTableName];
	cache.set_empty_key(-1);
	
	VCTTableStructure* pTabStruct = TableStructure(strTableName.c_str());
	int nSize = 0;
	if(pTabStruct)
		nSize = pTabStruct->vecFields.size();

	VCTAttributeRow row;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		if(ParseAttribute(row,nSize))
		{
			if(!Cache(strTableName.c_str(),row,m_Pos))
				cache[row.nOID] = pos;
		}
	}
}
/// \brief 解析节点拓扑
void VCTParser::ParseNodeTopology()
{
	VCTNodeTopo val;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		
		if(ParseNodeTopology(val))
			Cache(val,pos);
	}
	ReadToEndObject();
}

bool VCTParser::ParseNodeTopology(VCTNodeTopo& val)
{
	val.nObjID = _atoi64(CurrentLine());
	ParseRef(val.vecSubOid);

	return true;
}
/// \brief 解析边拓扑
void VCTParser::ParseEdgeTopology()
{
	VCTEdgeTopo val;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		
		if(ParseEdgeTopology(val))
			Cache(val,pos);
	}
}

bool VCTParser::ParseEdgeTopology(VCTEdgeTopo& val)
{
	std::vector<std::string> vec = Split(CurrentLine(),m_Separator.c_str());
	if(vec.size() < 5)
		return false;
	val.nObjID = _atoi64(vec[0].c_str());
	val.nFNodeID = _atoi64(vec[1].c_str());
	val.nTNodeID = _atoi64(vec[2].c_str());
	val.nLPolygonID = _atoi64(vec[3].c_str());
	val.nRPolygonID = _atoi64(vec[4].c_str());
	ReadToEndObject();
	return true;
}
/// \brief 解析聚合地物
void VCTParser::ParseAggregation()
{
	VCTAggregation val;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		val.vecSubOid.clear();
		if(ParseAggregation(val))
			Cache(val,pos);
	}

}
bool VCTParser::ParseAggregation(VCTAggregation& coll)
{
	coll.ObjHeader.bValid = false;
	if(!ParseObjectHead(coll.ObjHeader)) return false;
	ParseRef(coll.vecSubOid);
	ReadToEndObject();
	return true;
}
/// \brief 解析变长字符串
void VCTParser::ParseVarchar()
{
	VCTVarchar val;
	fpos_t pos;
	while(!ReadToEndSection())
	{
		if(IsNullOrEmpty(CurrentLine()))
			continue;
		pos = m_Pos;
		
		if(ParseVarchar(val))
			Cache(val,pos);
	}
}
bool VCTParser::ParseVarchar(VCTVarchar& val)
{
	if(!ReadToNoneEmpty()) return false;
	val.nObjID = _atoi64(CurrentLine());
	val.strText.clear();
	while(true)
	{
		const char* line = ReadLine();
		if(strlen(line) == 1 && line[0] == m_Head.chSeparator)
			break;
		val.strText+=line;
	}
	return true;
}
void VCTParser::Cache(VCTPoint &geo,fpos_t pos)
{
	Cache(VCT_POINT,geo.ObjHeader.strUserID,geo.ObjHeader.nObjID,pos);
}

void VCTParser::Cache(VCTLine &geo,fpos_t pos)
{
	Cache(VCT_LINE,geo.ObjHeader.strUserID,geo.ObjHeader.nObjID,pos);
}

void VCTParser::Cache(VCTPolygon &geo,fpos_t pos)
{
	Cache(VCT_POLYGON,geo.ObjHeader.strUserID,geo.ObjHeader.nObjID,pos);
}

void VCTParser::Cache(VCTSolid &geo,fpos_t pos)
{
	Cache(VCT_SOLID,geo.ObjHeader.strUserID,geo.ObjHeader.nObjID,pos);
}

void VCTParser::Cache(VCTNodeTopo &geo,fpos_t pos)
{
	m_NodeTopoIndex[geo.nObjID]  = pos;

}

void VCTParser::Cache(VCTEdgeTopo &geo,fpos_t pos)
{
	m_EdgeTopoIndex[geo.nObjID]  = pos;
}

void VCTParser::Cache(VCTAggregation &geo,fpos_t pos)
{
	Cache(VCT_AGGREGATION,geo.ObjHeader.strUserID,geo.ObjHeader.nObjID,pos);
}

void VCTParser::Cache(VCTAnnotation &geo,fpos_t pos)
{
	Cache(VCT_ANNOTATION,geo.ObjHeader.strUserID,geo.ObjHeader.nObjID,pos);
}
bool VCTParser::Cache(const char* tab,VCTAttributeRow &row,fpos_t pos)
{
	return false;
}


void VCTParser::Cache(VCTVarchar &val,fpos_t pos)
{
	m_VarCharIndex[val.nObjID] = pos;
}
void VCTParser::Cache(VCTStyle &style,fpos_t pos)
{
	m_StyleIndex[style.strID] = pos;
}
void VCTParser::Cache(VCT_GEOMETRY_TYPE gType,const std::string& code,VCTID id,fpos_t pos)
{
	google::dense_hash_map<std::string,IDCache>& idx = m_GeometryIndex[gType];
	if(idx.empty()) idx.set_empty_key(std::string());
	IDCache& cache = idx[code];
	if(cache.empty()) cache.set_empty_key(-1);
	cache[id] = pos;
	
}
/// \brief 获取表名称对应的表结构
VCTTableStructure* VCTParser::TableStructure(const char* tabname)
{
	std::vector<VCTTableStructure>::iterator it = m_TableStructures.begin();
	for(int i = 0 ;i<m_TableStructures.size();it++)
	{
		if(stricmp(m_TableStructures[i].strTableName.c_str(),tabname)==0)
			return &m_TableStructures[i];
	}
	return NULL;
}
/// \brief 常量缓存
std::map<std::string,std::string>& VCTParser::ConstantMap()
{
	return m_ConstantMap;
}
/// \brief 关系表
KeyCache& VCTParser::RelationTableIndex()
{
	return m_RelationTableIndex;
}


/// \brief 根据Feature表获得Feature的索引。
IDCache& VCTParser::GeometryIndex(VCTFeatureCode& code)
{ 
	google::dense_hash_map<std::string,IDCache> &cache = m_GeometryIndex[code.GeometryType];
	return cache[code.strUserID];
}
/// \brief 变长字符串缓存
IDCache& VCTParser::VarcharIndex()
{
	return m_VarCharIndex;
}
IDCache& VCTParser::NodeTopoIndex(VCTFeatureCode& code)
{
	return m_NodeTopoIndex;
}
IDCache& VCTParser::EdgeTopoIndex(VCTFeatureCode& code)
{
	return m_EdgeTopoIndex;
}


IDCache& VCTParser::AttributeIndex(VCTFeatureCode& code)
{
	return m_AttributeIndex[code.strUserID];
}
KeyCache  & VCTParser::StyleIndex()
{
	return m_StyleIndex;
}
/// \brief 从文件位置读取一个对象
bool VCTParser::ParseObject(fpos_t pos,VCTPoint& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	obj.vecLineOID.clear();
	obj.vecPoint.clear();
	return ParsePoint(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTLine& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	obj.vecArcID.clear();
	obj.vecLineData.clear();
	return ParseLine(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTPolygon& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	obj.PolygonIndrect.vecnSubOID.clear();
	obj.vecPolygonElement.clear();
	return ParsePolygon(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTSolid& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	obj.vecSolidElement.clear();
	obj.vecSubOid.clear();
	return ParseSolid(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTAnnotation& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	obj.vecAnnoPoint.clear();
	return ParseAnnotation(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTAttributeRow& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	obj.vecstrFieldValues.clear();
	return ParseAttribute(obj,0);
}


bool VCTParser::ParseObject(fpos_t pos,VCTVarchar& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	return ParseVarchar(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTConstant& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	return ParseConstant(obj);
}

bool VCTParser::ParseObject(fpos_t pos,VCTEdgeTopo& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	return ParseEdgeTopology(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTAggregation& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	return ParseAggregation(obj);
}
bool VCTParser::ParseObject(fpos_t pos,VCTNodeTopo& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	return ParseNodeTopology(obj);
}
 
bool VCTParser::ParseObject(fpos_t pos,VCTRelationTable& obj)
{
	m_fs.seekg(pos);
	if(m_fs.tellg().seekpos() != pos) return false;
	if(!ReadToNoneEmpty()) return false;
	return ParseRelationTable(obj);
}




bool VCTParser::Parse()
{
	m_fs.seekg(0);
	while(!m_fs.eof())
	{
		const char* pHead = ReadLine();
		if(stricmp(pHead,"HeadBegin") ==0)
		{
			while(!ReadToEndSection())
			{
				ParseHead(CurrentLine());
			}
		}
		else if(stricmp(pHead,"FeatureCodeBegin") ==0)
		{
			while(!ReadToEndSection())
			{
				ParseFeatureCode(CurrentLine());
			}
		}
		else if(stricmp(pHead,"TableStructureBegin") ==0)
			ParseTableStructure();
		else if(stricmp(pHead,"PointBegin") ==0)
			ParsePoint();
		else if(stricmp(pHead,"LineBegin") ==0)
			ParseLine();
		else if(stricmp(pHead,"PolygonBegin") ==0)
			ParsePolygon();
		else if(stricmp(pHead,"SolidBegin") ==0)
			ParseSolid();
		else if(stricmp(pHead,"AnnotationBegin")==0)
			ParseAnnotation();
		else if(stricmp(pHead,"AggregationBegin")==0)
			ParseAggregation();
		else if(stricmp(pHead,"TopologyBegin")==0)
		{
			while(!ReadToEndSection())
			{
				if(IsNullOrEmpty(CurrentLine()))
					continue;
				
				if(stricmp(pHead,"NodeTopologyBegin")==0)
					ParseNodeTopology();
				else if(stricmp(pHead,"EdgeTopologyBegin")==0)
					ParseEdgeTopology();
			}
		}
		else if(stricmp(pHead,"AttributeBegin") ==0)
		{
			while(!ReadToEndSection())
				ParseAttribute();
		}
		else if(stricmp(pHead,"StyleBegin") ==0)
		{
			while(!ReadToEndSection())
			{
				if(IsNullOrEmpty(CurrentLine()))
					continue;
				const char* pHead = CurrentLine();
				if(stricmp(pHead,"ConstantBegin") ==0)
					ParseConstant();
				else if(stricmp(pHead,"RelationTableBegin") ==0)
					ParseRelationTable();
				else if(stricmp(pHead,"RepresentationBegin") ==0)
					ParseRepresentation();
			}
		}
	}
	
	//清除eof标记
	m_fs.clear();  
	return true;
}
//读取到节的结尾
bool VCTParser::ReadToEndSection()
{ 
	const char* line = ReadLine();
	return EndWith(line,"End");
}
//当前行
const char* VCTParser::CurrentLine()
{
	return &m_LineCache[0];
}


VCTFeatureWriter::VCTFeatureWriter(VCTFeatureCode &code,VCTTempFilePtr ptrGeo,
	VCTTempFilePtr ptrAtt,VCTHead &head)
{
	m_Head = head;
	m_GeoTempFile = ptrGeo;
	m_AttTempFile = ptrAtt;
	m_Code = code;
}
VCTFeatureWriter::VCTFeatureWriter(const VCTFeatureWriter& rhs)
{
	m_Head = rhs.m_Head;
	m_GeoTempFile = rhs.m_GeoTempFile;
	m_AttTempFile = rhs.m_AttTempFile;
	m_Code = rhs.m_Code;
}
VCTFeatureWriter& VCTFeatureWriter::operator =(const VCTFeatureWriter& rhs)
{
	m_Head = rhs.m_Head;
	m_GeoTempFile = rhs.m_GeoTempFile;
	m_AttTempFile = rhs.m_AttTempFile;
	m_Code = rhs.m_Code;
	return *this;
}
void VCTFeatureWriter::Write(const VCTObjectHeader& vctObjectHeader)
{ 
	m_GeoTempFile->FS<<vctObjectHeader.nObjID<<std::endl;
	m_GeoTempFile->FS<<vctObjectHeader.strUserID<<std::endl;
	m_GeoTempFile->FS<<vctObjectHeader.strStyle<<std::endl;
}
void VCTFeatureWriter::Write(const VCTPoint3D &pt)
{
	
	m_GeoTempFile->FS<<std::setprecision(10)<<pt.x<<m_Head.chSeparator<<pt.y;
	if(m_Head.nDim>2) m_GeoTempFile->FS<<m_Head.chSeparator<<pt.z;

	m_GeoTempFile->FS<<std::endl;
}
void VCTFeatureWriter::Write(const std::vector<VCTPoint3D>& pts)
{
	std::vector<VCTPoint3D>::const_iterator it = pts.begin();
	m_GeoTempFile->FS<<std::setprecision(5);
	for(;it != pts.end();it++)
		Write(*it);
}
void VCTFeatureWriter::EndObject()
{
	m_GeoTempFile->FS<<"0"<<std::endl<<std::endl;
}
/// \brief 从文件位置读取一个对象
void VCTFeatureWriter::Write(VCTPoint& obj)
{
	if(!m_GeoTempFile) return;

	Write(obj.ObjHeader);
	
	//点的特征类型
	m_GeoTempFile->FS<<obj.FeatureType<<std::endl;
	//点数
	if (obj.FeatureType == VCT_POINT_GROUP)
		m_GeoTempFile->FS<<obj.vecPoint.size()<<std::endl;
	//坐标
	Write(obj.vecPoint) ;
	//对象结束
	EndObject();

}
void VCTFeatureWriter::Write(const std::vector<VCTID>& pts)
{
	m_GeoTempFile->FS<<pts.size()<<std::endl;
	std::vector<VCTID>::const_iterator it = pts.begin();
	int i =0;
	for(;it != pts.end();it++,i++)
	{
		if(i > 0 && i % 8==0)
			m_GeoTempFile->FS<<std::endl;
		
		m_GeoTempFile->FS<<*it;
	}
}
void VCTFeatureWriter::Write(VCTLine& obj)
{
	if(!m_GeoTempFile) return;

	Write(obj.ObjHeader);
	
	m_GeoTempFile->FS<<obj.FeatureType<<std::endl;
		
	//如果是直接坐标。
	if(obj.FeatureType == VCT_LINE_DIRECT)
	{
		if(obj.vecLineData.size() >0)
		{
			m_GeoTempFile->FS<<obj.vecLineData.size()<<std::endl;
			std::vector<VCTLineElement>::iterator it = obj.vecLineData.begin();
			for(;it != obj.vecLineData.end();it++)
			{
				m_GeoTempFile->FS<<it->GeometryType<<std::endl;
				m_GeoTempFile->FS<<it->vecArcPoint.size()<<std::endl;
				//坐标
				Write(it->vecArcPoint) ;
			}
		}
	}
	else //间接坐标。 
		Write(obj.vecArcID);

	//对象结束
	EndObject();
}
void VCTFeatureWriter::Write(VCTPolygon& obj)
{
	if(!m_GeoTempFile) return;

	Write(obj.ObjHeader);
	
	m_GeoTempFile->FS<<obj.FeatureType<<std::endl;
	Write(obj.LabPoint);
	//如果是直接坐标。
	if(obj.FeatureType == VCT_POLYGON_DIRECT)
	{
		if(obj.vecPolygonElement.size() >0)
		{
			m_GeoTempFile->FS<<obj.vecPolygonElement.size()<<std::endl;
			std::vector<VCTPolygonElement>::iterator it = obj.vecPolygonElement.begin();
			for(;it != obj.vecPolygonElement.end();it++)
			{
				m_GeoTempFile->FS<<it->GeoType<<std::endl;
				m_GeoTempFile->FS<<it->vecPoints.size()<<std::endl;
				//坐标
				Write(it->vecPoints) ;
			}
		}
	}
	else //间接坐标。 
	{
		m_GeoTempFile->FS<<obj.PolygonIndrect.IndirectType<<std::endl;
		Write(obj.PolygonIndrect.vecnSubOID);
	}
	 
	//对象结束
	EndObject();
}
void VCTFeatureWriter::Write(VCTSolid& obj)
{
	if(!m_GeoTempFile) return;

	Write(obj.ObjHeader);
	
	m_GeoTempFile->FS<<obj.FeatureType<<std::endl;
	Write(obj.LabPoibt);
	//如果是直接坐标。
	if(obj.FeatureType == VCT_SOLID_DIRECT)
	{
		if(obj.vecSolidElement.size() >0)
		{
			m_GeoTempFile->FS<<obj.vecSolidElement.size()<<std::endl;
			std::vector<VCTSolidElement>::iterator it = obj.vecSolidElement.begin();
			for(;it != obj.vecSolidElement.end();it++)
			{ 
				m_GeoTempFile->FS<<it->PolygonElement.GeoType<<std::endl;
				m_GeoTempFile->FS<<it->PolygonElement.vecPoints.size()<<std::endl;
				//坐标
				Write(it->PolygonElement.vecPoints) ;
			}
		}
	}
	else //间接坐标。 
	{ 
		m_GeoTempFile->FS<<obj.nSubType<<std::endl;
		Write(obj.vecSubOid);
	}
	 
	//对象结束
	EndObject();
}
void VCTFeatureWriter::Write(VCTAnnotation& obj)
{
	if(!m_GeoTempFile) return;

	Write(obj.ObjHeader);
	
	m_GeoTempFile->FS<<obj.FeatureType<<std::endl;
	
	//注记内容
	m_GeoTempFile->FS<<obj.strText<<std::endl;
		
	//如果是多点注记，则还需要写点数
	if ( VCT_ANNO_MULTIPLE == obj.FeatureType)
		m_GeoTempFile->FS<<obj.vecAnnoPoint.size()<<std::endl;

	std::vector<VCTAnnoPoint>::iterator it = obj.vecAnnoPoint.begin();
	for(;it != obj.vecAnnoPoint.end();it++)
	{
			
		m_GeoTempFile->FS<<std::setprecision(10)<<it->vctPoint3D.x<<m_Head.chSeparator<<it->vctPoint3D.y;
		if(m_Head.nDim>2) m_GeoTempFile->FS<<m_Head.chSeparator<<it->vctPoint3D.z;
		
		m_GeoTempFile->FS<<m_Head.chSeparator<<it->fShiftDegree;
		m_GeoTempFile->FS<<std::endl;

	}
	//对象结束
	EndObject();

}
void VCTFeatureWriter::Write(VCTAggregation& obj)
{
	if(!m_AttTempFile) return;
	Write(obj.ObjHeader);
	Write(obj.vecSubOid);
	 //对象结束
	EndObject();
}
void VCTFeatureWriter::Write(VCTAttributeRow& obj)
{
	if(!m_AttTempFile) return;
	m_AttTempFile->FS<<obj.nOID;
	std::string strSep;
	strSep.push_back(m_Head.chSeparator);
	std::vector<std::string>::iterator it = obj.vecstrFieldValues.begin();
	for(;it != obj.vecstrFieldValues.end();it++)
	{
		m_AttTempFile->FS<<m_Head.chSeparator;
		m_AttTempFile->FS<<Replace(it->c_str(),strSep.c_str(),"，");
	}
	m_AttTempFile->FS<<std::endl;
}
	

 

VCTWriter::VCTWriter(const char* strVCT)
{
	m_strVCTFile = strVCT;
}
VCTFeatureWriter VCTWriter::BeginFeature(VCTFeatureCode& code,VCTTableStructure tab)
{
	m_FeatureCodes.push_back(std::pair<VCTFeatureCode,VCTTableStructure>(code,tab));
	std::string strGeoKey;
	switch(code.GeometryType)
	{
	case VCT_POINT:// = 0, 						// 点状要素
		strGeoKey ="Point";
		break;
	case VCT_LINE:// = 1, 						// 线状要素
		strGeoKey ="Line";
		break;
	case VCT_POLYGON:// = 2,						// 面状要素
		strGeoKey ="Polygon";
		break;
	case VCT_SOLID:// = 3,						// 体要素			
		strGeoKey ="Solid";
		break;
	case VCT_AGGREGATION:// = 3,						// 聚合			
		strGeoKey ="Agg";
		break;
	case VCT_ANNOTATION:// = 5,					// 注记
		strGeoKey ="ANN";
		break;
	}
	VCTTempFilePtr &ptrTemp = m_StreamWrite[strGeoKey];
	if(!ptrTemp)
	{
		ptrTemp.reset(new VCTTempFile());
		ptrTemp->File = m_strVCTFile;
		ptrTemp->File+=".";
		ptrTemp->File+=strGeoKey;
		ptrTemp->Type = (VCTTempFileType)code.GeometryType;
		ptrTemp->FS.open(ptrTemp->File.c_str(),std::ios_base::app);
		ptrTemp->FS<<std::setprecision(10);

	}

	std::string strAttKey = "Attribute";
	
	if(code.strAttributeTableName.empty())
		code.strAttributeTableName =  code.strUserID;
	strAttKey+=code.strAttributeTableName;
	VCTTempFilePtr &ptrAtt = m_StreamWrite[strAttKey];
	if(!ptrAtt)
	{
		ptrAtt.reset(new VCTTempFile());
		ptrAtt->File = m_strVCTFile;
		ptrAtt->File+=".";
		ptrAtt->File+=strAttKey;
		ptrAtt->Type = eAttributeFile;
		ptrAtt->FS.open(ptrAtt->File.c_str(),std::ios_base::app);
		//将属性表的表头写入。
		ptrAtt->FS<<code.strAttributeTableName<<std::endl;
	}
	
	return VCTFeatureWriter(code,ptrTemp,ptrAtt,m_Head);
}

void VCTWriter::Write(VCTRelationTable& tab)
{
	VCTTempFilePtr &ptrTemp = m_StreamWrite["RelationTable"];
	if(!ptrTemp)
	{
		ptrTemp.reset(new VCTTempFile());
		ptrTemp->File = m_strVCTFile;
		ptrTemp->File+=".RelationTable";
		ptrTemp->Type = eRelationTableFile;
		ptrTemp->FS.open(ptrTemp->File.c_str(),std::ios_base::app);
	}
	ptrTemp->FS<<tab.strTableID<<std::endl;
	

	std::vector<VCTPairEx>::iterator it = tab.vecRelationPairs.begin();
	for(;it != tab.vecRelationPairs.end();it++)
	{
		ptrTemp->FS<<it->strKey<<m_Head.chSeparator<<it->strValue;
		std::vector<std::string>::iterator itStr = it->strVecAlias.begin();
		for(;itStr != it->strVecAlias.end();itStr++)
		{
			ptrTemp->FS<<m_Head.chSeparator<<*itStr;
		}
		ptrTemp->FS<<std::endl;
	}
	ptrTemp->FS<<"\0"<<std::endl;

}
void VCTWriter::Write(const char* key,const char* value)
{
	m_ConstantMap[key] = value;
}

/// \brief 写入变长字符串。
void VCTWriter::Write(VCTID id,const char* value)
{
	VCTTempFilePtr &ptrTemp = m_StreamWrite["Varchar"];
	if(!ptrTemp)
	{
		ptrTemp.reset(new VCTTempFile());
		ptrTemp->File = m_strVCTFile;
		ptrTemp->File+=".Varchar";
		ptrTemp->Type = eVarcharFile;
		ptrTemp->FS.open(ptrTemp->File.c_str(),std::ios_base::app);
	}
	ptrTemp->FS<<id<<std::endl;
	
	ptrTemp->FS<<value<<std::endl;
	ptrTemp->FS<<m_Head.chSeparator<<std::endl;
}
void VCTWriter::Write(VCTStyle& style)
{
	VCTTempFilePtr &ptrTemp = m_StreamWrite["Style"];
	if(!ptrTemp)
	{
		ptrTemp.reset(new VCTTempFile());
		ptrTemp->File = m_strVCTFile;
		ptrTemp->File+=".Style";
		ptrTemp->Type = eStyleFile;
		ptrTemp->FS.open(ptrTemp->File.c_str(),std::ios_base::app);
	}
	ptrTemp->FS<<style.strID<<std::endl;
	ptrTemp->FS<<style.vecPairs.size()<<std::endl;

	std::vector<VCTPairEx>::iterator it = style.vecPairs.begin();
	for(;it != style.vecPairs.end();it++)
	{
		ptrTemp->FS<<it->strKey<<m_Head.chSeparator<<it->strValue;
		std::vector<std::string>::iterator itStr = it->strVecAlias.begin();
		for(;itStr != it->strVecAlias.end();itStr++)
		{
			ptrTemp->FS<<m_Head.chSeparator<<*itStr;
		}
		ptrTemp->FS<<std::endl;
	}
	ptrTemp->FS<<"\0"<<std::endl;
}
VCTHead& VCTWriter::Head()
{
	return m_Head;
}
//保存头
void VCTWriter::SaveHead(std::ofstream& fs)
{
	//  写文件头
	fs<<"HeadBegin"<<std::endl;
	fs<<"DataMark:"<<m_Head.strDataMark<<std::endl;
	fs<<"Version:"<<m_Head.strVersion<<std::endl;

	if (!m_Head.strCSType.empty())		fs<<"CoordinateSystemType:"<<m_Head.strCSType<<std::endl;
	if (m_Head.nDim > 0)				fs<<"Dim:"<<m_Head.nDim<<std::endl;
	if (!m_Head.strXAxis.empty())		fs<<"XAxisDirection:"<<m_Head.strXAxis<<std::endl;
	if (!m_Head.strYAxis.empty())		fs<<"YAxisDirection:"<<m_Head.strYAxis<<std::endl;
	if (!m_Head.strXYUnit.empty())		fs<<"XYUnit:"<<m_Head.strXYUnit<<std::endl;
	if (!m_Head.strZUnit.empty())		fs<<"ZUnit:"<<m_Head.strZUnit<<std::endl;
	if (!m_Head.strSpheroid.empty())	fs<<"Spheroid:"<<m_Head.strSpheroid<<std::endl; 
	if (!m_Head.strPM.empty())			fs<<"PrimeMeridian:"<<m_Head.strPM<<std::endl; 
	if (!m_Head.strProjection.empty())	fs<<"Projection:"<<m_Head.strProjection<<std::endl; 
	if (!m_Head.strParameters.empty())	fs<<"Parameters:"<<m_Head.strParameters<<std::endl; 
	if (!m_Head.strVerticalCRS.empty())	fs<<"VerticalDatum:"<<m_Head.strVerticalCRS<<std::endl; 
	if (!m_Head.strTimeRS.empty())		fs<<"TemporalReferenceSystem:"<<m_Head.strTimeRS<<std::endl; 
	if(m_Head.dfMinX > -DBL_MAX && m_Head.dfMinX < DBL_MAX &&
		m_Head.dfMinY > -DBL_MAX && m_Head.dfMinY < DBL_MAX )
	{
		fs<<"ExtentMin:"<<std::setprecision(8)<<m_Head.dfMinX<<m_Head.chSeparator<<m_Head.dfMinY;
		if(m_Head.dfMinZ > -DBL_MAX && m_Head.dfMinZ < DBL_MAX)
			fs<<m_Head.chSeparator<<m_Head.dfMinZ;
		fs<<std::endl;
	}
	if(m_Head.dfMaxX > -DBL_MAX && m_Head.dfMaxX < DBL_MAX &&
		m_Head.dfMaxY > -DBL_MAX && m_Head.dfMaxY < DBL_MAX )
	{
		fs<<"ExtentMax:"<<std::setprecision(8)<<m_Head.dfMaxX<<m_Head.chSeparator<<m_Head.dfMaxY;
		if(m_Head.dfMaxZ > -DBL_MAX && m_Head.dfMaxZ < DBL_MAX)
			fs<<m_Head.chSeparator<<m_Head.dfMinZ;
		fs<<std::endl;
	}
	if (m_Head.nScaleM  !=0)		fs<<"MapScale:"<<m_Head.nScaleM<<std::endl; 
	if (m_Head.dOffsetX !=0 ||m_Head.dOffsetY !=0)
	{
		fs<<"Offset:"<<m_Head.dOffsetX<<m_Head.chSeparator<<m_Head.dOffsetY; 
		if(m_Head.dOffsetZ != 0)
			fs<<m_Head.chSeparator<<m_Head.dOffsetZ;
		fs<<std::endl;
	}
	if (!m_Head.strDate.empty())		fs<<"Date:"<<m_Head.strDate<<std::endl; 
	
	fs<<"Separator:"<<m_Head.chSeparator<<std::endl; 

	fs<<"HeadEnd"<<std::endl<<std::endl;

}

void VCTWriter::CopyFile(std::ofstream& fs,VCTTempFilePtr& ptrFile)
{
	m_LineCache.resize(1024*1024);
	char* head = &m_LineCache[0];
	//关闭原有的写文件。
	ptrFile->FS.close();


	{
		//逐行写入。
		std::ifstream s(ptrFile->File.c_str());
		while(!s.eof())
		{
			s.getline(head,m_LineCache.size());
			fs<<head<<std::endl;
		}
	}

	remove(ptrFile->File.c_str());


}
struct VCTSectionWriter
{
	std::ofstream &m_FS;
	std::string m_strName;
	VCTSectionWriter(std::ofstream &fs,const char* name):m_FS(fs)
	{
		m_strName = name;
		m_FS<<m_strName<<"Begin"<<std::endl;
	}
	~VCTSectionWriter()
	{
		m_FS<<m_strName<<"End"<<std::endl<<std::endl;
	}

	
};
/// \brief 结束所有数据写入之后调用此函数提交数据到最终文件。
void VCTWriter::Finish()
{
	std::ofstream fs(m_strVCTFile.c_str());
	SaveHead(fs);

	std::vector<std::pair<VCTFeatureCode,VCTTableStructure>>::iterator it = m_FeatureCodes.begin();
	{
		VCTSectionWriter sec(fs,"FeatureCode");
		for(;it != m_FeatureCodes.end();it++)
		{
			fs<<it->first.strUserID<<m_Head.chSeparator<<it->first.strName<<m_Head.chSeparator
				<<CEnumParser::ToString(it->first.GeometryType,"Point")<<m_Head.chSeparator<<
				it->first.strAttributeTableName;
			if(!it->first.strUserItem.empty())
				fs<<m_Head.chSeparator<<it->first.strUserItem;
			fs<<std::endl;
		}
	}
	{
		VCTSectionWriter sec(fs,"TableStructure"); 
		it = m_FeatureCodes.begin();
		for(;it != m_FeatureCodes.end();it++)
		{
			fs<<it->second.strTableName<<m_Head.chSeparator<<it->second.vecFields.size();
			if(!it->second.bGeometry)
				fs<<m_Head.chSeparator<<"NoneGeometry";
			fs<<std::endl;
			std::vector<VCTField>::iterator itF = it->second.vecFields.begin();
			for(;itF != it->second.vecFields.end();itF++)
			{
				fs<<itF->strFieldName<<m_Head.chSeparator<<
					CEnumParser::ToString(itF->FieldType,"Char");
				if(itF->FieldType == VCT_CHAR)
					fs<<m_Head.chSeparator<<itF->nWidth;
				else if(itF->FieldType == VCT_FLOAT || itF->FieldType == VCT_DOUBLE ||itF->FieldType == VCT_NUMERIC)
				{
					if(itF->nWidth > 0) fs<<m_Head.chSeparator<<itF->nWidth;
					if(itF->nPrecision > 0) fs<<m_Head.chSeparator<<itF->nPrecision;
				}
				else if(itF->FieldType == VCT_DATE)
					fs<<m_Head.chSeparator<<8;

				fs<<std::endl;
			}

			fs<<"0"<<std::endl<<std::endl;
		} 
	}
	
	//缓存所有的属性文件。
	std::vector<VCTTempFilePtr> vecAtt;
	//缓存所有的式样文件
	std::vector<VCTTempFilePtr> vecStyle;

	//准备写入所有点、线、面文件。
	std::map<std::string,VCTTempFilePtr >::iterator itF =  m_StreamWrite.begin();
	for(;itF != m_StreamWrite.end();itF++)
	{
		//属性表集中起来写入。
		if(itF->second->Type == eAttributeFile)
		{
			vecAtt.push_back(itF->second);
			continue;
		}
		else if(itF->second->Type == eStyleFile) //式样
		{
			vecStyle.push_back(itF->second);
			continue;
		}
		else if(itF->second->Type == eRelationTableFile)//关系表
		{
			vecStyle.push_back(itF->second);
			continue;
		}
		if(itF->second->Type == eVarcharFile)
		{
			VCTSectionWriter sec(fs,"Varchar"); 
			CopyFile(fs,itF->second);
		}
		else if(itF->second->Type == ePointFile)
		{
			VCTSectionWriter sec(fs,"Point"); 
			CopyFile(fs,itF->second);
		}
		else if(itF->second->Type == eLineFile)
		{
			VCTSectionWriter sec(fs,"Line"); 
			CopyFile(fs,itF->second);
		}
		else if(itF->second->Type == ePolygonFile)
		{
			VCTSectionWriter sec(fs,"Polygon"); 
			CopyFile(fs,itF->second);
		}
		else if(itF->second->Type == eAnnotationFile)
		{
			VCTSectionWriter sec(fs,"Annotation"); 
			CopyFile(fs,itF->second);
		}
	}

	//写入属性文件。
	if(!vecAtt.empty())
	{
		VCTSectionWriter sec(fs,"Attribute"); 
		std::vector<VCTTempFilePtr>::iterator itA =  vecAtt.begin();
		for(;itA != vecAtt.end();itA++)
		{
			CopyFile(fs,*itA);
			fs<<"TableEnd"<<std::endl<<std::endl;
		}
	}

	//如果存在式样文件或者常量表
	if(!vecStyle.empty() || m_ConstantMap.empty())
	{
		VCTSectionWriter sec(fs,"Style"); 
		if(m_ConstantMap.empty()) //常数列表
		{
			VCTSectionWriter s(fs,"Constant"); 
			std::map<std::string,std::string>::iterator it  = m_ConstantMap.begin(); //常量。
			for(;it != m_ConstantMap.end();it++)
			{
				fs<<it->first<<m_Head.chSeparator<<it->second<<std::endl;
			}
		}
		std::vector<VCTTempFilePtr>::iterator itA =  vecStyle.begin();
		for(;itA != vecStyle.end();itA++)
		{
			if((*itA)->Type == eRelationTableFile)
			{
				VCTSectionWriter s(fs,"RelationTable"); 
				CopyFile(fs,*itA);
			}
			else if((*itA)->Type == eStyleFile)
			{
				VCTSectionWriter s(fs,"Representation"); 
				CopyFile(fs,*itA);
			}
		}
	}
}