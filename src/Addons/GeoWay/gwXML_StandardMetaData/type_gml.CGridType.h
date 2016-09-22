#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridType

#include "type_gml.CAbstractGeometryType.h"


namespace gie
{

namespace gml
{	

class CGridType : public ::gie::gml::CAbstractGeometryType
{
public:
	gie_EXPORT CGridType(xercesc::DOMNode* const& init);
	gie_EXPORT CGridType(CGridType const& init);
	void operator=(CGridType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGridType); }

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CGridType_altova_dimension, 0, 0> dimension;	// dimension CpositiveInteger
	MemberElement<gml::CGridLimitsType, _altova_mi_gml_altova_CGridType_altova_limits> limits;
	struct limits { typedef Iterator<gml::CGridLimitsType> iterator; };
	MemberElement<gml::CNCNameListType, _altova_mi_gml_altova_CGridType_altova_axisLabels2> axisLabels2;
	struct axisLabels2 { typedef Iterator<gml::CNCNameListType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CGridType_altova_axisName> axisName;
	struct axisName { typedef Iterator<xs::CstringType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridType
