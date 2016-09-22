#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoCurveType

#include "type_gml.CAbstractTopologyType.h"


namespace gie
{

namespace gml
{	

class CTopoCurveType : public ::gie::gml::CAbstractTopologyType
{
public:
	gie_EXPORT CTopoCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoCurveType(CTopoCurveType const& init);
	void operator=(CTopoCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoCurveType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoCurveType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDirectedEdgePropertyType, _altova_mi_gml_altova_CTopoCurveType_altova_directedEdge> directedEdge;
	struct directedEdge { typedef Iterator<gml::CDirectedEdgePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoCurveType
