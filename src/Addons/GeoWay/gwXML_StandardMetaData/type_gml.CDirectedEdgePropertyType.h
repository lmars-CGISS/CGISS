#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedEdgePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedEdgePropertyType



namespace gie
{

namespace gml
{	

class CDirectedEdgePropertyType : public TypeBase
{
public:
	gie_EXPORT CDirectedEdgePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectedEdgePropertyType(CDirectedEdgePropertyType const& init);
	void operator=(CDirectedEdgePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectedEdgePropertyType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_orientation, 0, 2> orientation;	// orientation CSignType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CDirectedEdgePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CEdgeType, _altova_mi_gml_altova_CDirectedEdgePropertyType_altova_Edge> Edge;
	struct Edge { typedef Iterator<gml::CEdgeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedEdgePropertyType
