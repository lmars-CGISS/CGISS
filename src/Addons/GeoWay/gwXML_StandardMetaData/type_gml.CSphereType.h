#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSphereType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSphereType

#include "type_gml.CAbstractGriddedSurfaceType.h"


namespace gie
{

namespace gml
{	

class CSphereType : public ::gie::gml::CAbstractGriddedSurfaceType
{
public:
	gie_EXPORT CSphereType(xercesc::DOMNode* const& init);
	gie_EXPORT CSphereType(CSphereType const& init);
	void operator=(CSphereType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSphereType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CSphereType_altova_horizontalCurveType, 0, 11> horizontalCurveType;	// horizontalCurveType CCurveInterpolationType
	MemberAttribute<string_type,_altova_mi_gml_altova_CSphereType_altova_verticalCurveType, 0, 11> verticalCurveType;	// verticalCurveType CCurveInterpolationType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSphereType
