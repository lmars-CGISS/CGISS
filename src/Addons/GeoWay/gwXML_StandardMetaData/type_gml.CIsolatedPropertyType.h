#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIsolatedPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIsolatedPropertyType



namespace gie
{

namespace gml
{	

class CIsolatedPropertyType : public TypeBase
{
public:
	gie_EXPORT CIsolatedPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CIsolatedPropertyType(CIsolatedPropertyType const& init);
	void operator=(CIsolatedPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CIsolatedPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CIsolatedPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CIsolatedPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CNodeType, _altova_mi_gml_altova_CIsolatedPropertyType_altova_Node> Node;
	struct Node { typedef Iterator<gml::CNodeType> iterator; };
	MemberElement<gml::CEdgeType, _altova_mi_gml_altova_CIsolatedPropertyType_altova_Edge> Edge;
	struct Edge { typedef Iterator<gml::CEdgeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIsolatedPropertyType
