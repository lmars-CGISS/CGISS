#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CQuantityPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CQuantityPropertyType



namespace gie
{

namespace gml
{	

class CQuantityPropertyType : public TypeBase
{
public:
	gie_EXPORT CQuantityPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CQuantityPropertyType(CQuantityPropertyType const& init);
	void operator=(CQuantityPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CQuantityPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CQuantityPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gie2::CQuantityType, _altova_mi_gml_altova_CQuantityPropertyType_altova_Quantity> Quantity;
	struct Quantity { typedef Iterator<gie2::CQuantityType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CQuantityPropertyType
