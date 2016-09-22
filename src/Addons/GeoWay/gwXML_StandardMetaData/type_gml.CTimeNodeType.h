#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeNodeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeNodeType

#include "type_gml.CAbstractTimeTopologyPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CTimeNodeType : public ::gie::gml::CAbstractTimeTopologyPrimitiveType
{
public:
	gie_EXPORT CTimeNodeType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeNodeType(CTimeNodeType const& init);
	void operator=(CTimeNodeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeNodeType); }
	MemberElement<gml::CTimeEdgePropertyType, _altova_mi_gml_altova_CTimeNodeType_altova_previousEdge> previousEdge;
	struct previousEdge { typedef Iterator<gml::CTimeEdgePropertyType> iterator; };
	MemberElement<gml::CTimeEdgePropertyType, _altova_mi_gml_altova_CTimeNodeType_altova_nextEdge> nextEdge;
	struct nextEdge { typedef Iterator<gml::CTimeEdgePropertyType> iterator; };
	MemberElement<gml::CTimeInstantPropertyType, _altova_mi_gml_altova_CTimeNodeType_altova_position> position;
	struct position { typedef Iterator<gml::CTimeInstantPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeNodeType
