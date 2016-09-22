#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractParametricCurveSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractParametricCurveSurfaceType

#include "type_gml.CAbstractSurfacePatchType.h"


namespace gie
{

namespace gml
{	

class CAbstractParametricCurveSurfaceType : public ::gie::gml::CAbstractSurfacePatchType
{
public:
	gie_EXPORT CAbstractParametricCurveSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractParametricCurveSurfaceType(CAbstractParametricCurveSurfaceType const& init);
	void operator=(CAbstractParametricCurveSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractParametricCurveSurfaceType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractParametricCurveSurfaceType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractParametricCurveSurfaceType
