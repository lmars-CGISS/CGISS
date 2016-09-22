#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COffsetCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COffsetCurveType

#include "type_gml.CAbstractCurveSegmentType.h"


namespace gie
{

namespace gml
{	

class COffsetCurveType : public ::gie::gml::CAbstractCurveSegmentType
{
public:
	gie_EXPORT COffsetCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT COffsetCurveType(COffsetCurveType const& init);
	void operator=(COffsetCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_COffsetCurveType); }
	MemberElement<gml::CCurvePropertyType, _altova_mi_gml_altova_COffsetCurveType_altova_offsetBase> offsetBase;
	struct offsetBase { typedef Iterator<gml::CCurvePropertyType> iterator; };
	MemberElement<gml::CLengthType, _altova_mi_gml_altova_COffsetCurveType_altova_distance> distance;
	struct distance { typedef Iterator<gml::CLengthType> iterator; };
	MemberElement<gml::CVectorType, _altova_mi_gml_altova_COffsetCurveType_altova_refDirection> refDirection;
	struct refDirection { typedef Iterator<gml::CVectorType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COffsetCurveType
