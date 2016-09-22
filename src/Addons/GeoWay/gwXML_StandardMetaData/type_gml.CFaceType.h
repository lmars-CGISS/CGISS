#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFaceType

#include "type_gml.CAbstractTopoPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CFaceType : public ::gie::gml::CAbstractTopoPrimitiveType
{
public:
	gie_EXPORT CFaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CFaceType(CFaceType const& init);
	void operator=(CFaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFaceType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CFaceType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDirectedEdgePropertyType, _altova_mi_gml_altova_CFaceType_altova_directedEdge> directedEdge;
	struct directedEdge { typedef Iterator<gml::CDirectedEdgePropertyType> iterator; };
	MemberElement<gml::CDirectedTopoSolidPropertyType, _altova_mi_gml_altova_CFaceType_altova_directedTopoSolid> directedTopoSolid;
	struct directedTopoSolid { typedef Iterator<gml::CDirectedTopoSolidPropertyType> iterator; };
	MemberElement<gml::CSurfacePropertyType, _altova_mi_gml_altova_CFaceType_altova_surfaceProperty> surfaceProperty;
	struct surfaceProperty { typedef Iterator<gml::CSurfacePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFaceType
