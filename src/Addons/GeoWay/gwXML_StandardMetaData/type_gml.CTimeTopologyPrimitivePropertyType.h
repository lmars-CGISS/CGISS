#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyPrimitivePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyPrimitivePropertyType



namespace gie
{

namespace gml
{	

class CTimeTopologyPrimitivePropertyType : public TypeBase
{
public:
	gie_EXPORT CTimeTopologyPrimitivePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeTopologyPrimitivePropertyType(CTimeTopologyPrimitivePropertyType const& init);
	void operator=(CTimeTopologyPrimitivePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeTopologyPrimitivePropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CTimeEdgeType, _altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_TimeEdge> TimeEdge;
	struct TimeEdge { typedef Iterator<gml::CTimeEdgeType> iterator; };
	MemberElement<gml::CTimeNodeType, _altova_mi_gml_altova_CTimeTopologyPrimitivePropertyType_altova_TimeNode> TimeNode;
	struct TimeNode { typedef Iterator<gml::CTimeNodeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyPrimitivePropertyType
