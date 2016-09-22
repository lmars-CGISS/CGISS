#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodesicStringType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodesicStringType

#include "type_gml.CAbstractCurveSegmentType.h"


namespace gie
{

namespace gml
{	

class CGeodesicStringType : public ::gie::gml::CAbstractCurveSegmentType
{
public:
	gie_EXPORT CGeodesicStringType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeodesicStringType(CGeodesicStringType const& init);
	void operator=(CGeodesicStringType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeodesicStringType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodesicStringType_altova_interpolation, 0, 11> interpolation;	// interpolation CCurveInterpolationType
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CGeodesicStringType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CGeodesicStringType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CGeodesicStringType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodesicStringType
