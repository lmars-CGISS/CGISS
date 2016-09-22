#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSurfaceType

#include "type_gml.CAbstractGeometricAggregateType.h"


namespace gie
{

namespace gml
{	

class CMultiSurfaceType : public ::gie::gml::CAbstractGeometricAggregateType
{
public:
	gie_EXPORT CMultiSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiSurfaceType(CMultiSurfaceType const& init);
	void operator=(CMultiSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiSurfaceType); }
	MemberElement<gml::CSurfacePropertyType, _altova_mi_gml_altova_CMultiSurfaceType_altova_surfaceMember> surfaceMember;
	struct surfaceMember { typedef Iterator<gml::CSurfacePropertyType> iterator; };
	MemberElement<gml::CSurfaceArrayPropertyType, _altova_mi_gml_altova_CMultiSurfaceType_altova_surfaceMembers> surfaceMembers;
	struct surfaceMembers { typedef Iterator<gml::CSurfaceArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSurfaceType
