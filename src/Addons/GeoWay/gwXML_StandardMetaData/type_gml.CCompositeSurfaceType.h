#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeSurfaceType

#include "type_gml.CAbstractSurfaceType.h"


namespace gie
{

namespace gml
{	

class CCompositeSurfaceType : public ::gie::gml::CAbstractSurfaceType
{
public:
	gie_EXPORT CCompositeSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CCompositeSurfaceType(CCompositeSurfaceType const& init);
	void operator=(CCompositeSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCompositeSurfaceType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CCompositeSurfaceType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CSurfacePropertyType, _altova_mi_gml_altova_CCompositeSurfaceType_altova_surfaceMember> surfaceMember;
	struct surfaceMember { typedef Iterator<gml::CSurfacePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeSurfaceType
