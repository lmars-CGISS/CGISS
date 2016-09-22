#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCountPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCountPropertyType



namespace gie
{

namespace gml
{	

class CCountPropertyType : public TypeBase
{
public:
	gie_EXPORT CCountPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCountPropertyType(CCountPropertyType const& init);
	void operator=(CCountPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCountPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CCountPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gie2::CCountType, _altova_mi_gml_altova_CCountPropertyType_altova_Count> Count;
	struct Count { typedef Iterator<gie2::CCountType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCountPropertyType
