#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COrientableCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COrientableCurveType

#include "type_gml.CAbstractCurveType.h"


namespace gie
{

namespace gml
{	

class COrientableCurveType : public ::gie::gml::CAbstractCurveType
{
public:
	gie_EXPORT COrientableCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT COrientableCurveType(COrientableCurveType const& init);
	void operator=(COrientableCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_COrientableCurveType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_COrientableCurveType_altova_orientation, 0, 2> orientation;	// orientation CSignType
	MemberElement<gml::CCurvePropertyType, _altova_mi_gml_altova_COrientableCurveType_altova_baseCurve> baseCurve;
	struct baseCurve { typedef Iterator<gml::CCurvePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COrientableCurveType
