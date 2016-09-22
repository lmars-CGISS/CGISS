#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedNodePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedNodePropertyType



namespace gie
{

namespace gml
{	

class CDirectedNodePropertyType : public TypeBase
{
public:
	gie_EXPORT CDirectedNodePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectedNodePropertyType(CDirectedNodePropertyType const& init);
	void operator=(CDirectedNodePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectedNodePropertyType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_orientation, 0, 2> orientation;	// orientation CSignType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CDirectedNodePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CNodeType, _altova_mi_gml_altova_CDirectedNodePropertyType_altova_Node> Node;
	struct Node { typedef Iterator<gml::CNodeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedNodePropertyType
