#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCylinderType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCylinderType

#include "type_gml.CAbstractGriddedSurfaceType.h"


namespace gie
{

namespace gml
{	

class CCylinderType : public ::gie::gml::CAbstractGriddedSurfaceType
{
public:
	gie_EXPORT CCylinderType(xercesc::DOMNode* const& init);
	gie_EXPORT CCylinderType(CCylinderType const& init);
	void operator=(CCylinderType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCylinderType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CCylinderType_altova_horizontalCurveType, 0, 11> horizontalCurveType;	// horizontalCurveType CCurveInterpolationType
	MemberAttribute<string_type,_altova_mi_gml_altova_CCylinderType_altova_verticalCurveType, 0, 11> verticalCurveType;	// verticalCurveType CCurveInterpolationType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCylinderType
