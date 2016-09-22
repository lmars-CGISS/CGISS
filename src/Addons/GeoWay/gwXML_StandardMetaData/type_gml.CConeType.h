#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConeType

#include "type_gml.CAbstractGriddedSurfaceType.h"


namespace gie
{

namespace gml
{	

class CConeType : public ::gie::gml::CAbstractGriddedSurfaceType
{
public:
	gie_EXPORT CConeType(xercesc::DOMNode* const& init);
	gie_EXPORT CConeType(CConeType const& init);
	void operator=(CConeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CConeType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CConeType_altova_horizontalCurveType, 0, 11> horizontalCurveType;	// horizontalCurveType CCurveInterpolationType
	MemberAttribute<string_type,_altova_mi_gml_altova_CConeType_altova_verticalCurveType, 0, 11> verticalCurveType;	// verticalCurveType CCurveInterpolationType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConeType
