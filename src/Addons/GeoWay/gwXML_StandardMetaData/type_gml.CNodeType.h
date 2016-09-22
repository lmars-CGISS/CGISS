#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNodeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNodeType

#include "type_gml.CAbstractTopoPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CNodeType : public ::gie::gml::CAbstractTopoPrimitiveType
{
public:
	gie_EXPORT CNodeType(xercesc::DOMNode* const& init);
	gie_EXPORT CNodeType(CNodeType const& init);
	void operator=(CNodeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CNodeType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CNodeType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDirectedEdgePropertyType, _altova_mi_gml_altova_CNodeType_altova_directedEdge> directedEdge;
	struct directedEdge { typedef Iterator<gml::CDirectedEdgePropertyType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CNodeType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNodeType
