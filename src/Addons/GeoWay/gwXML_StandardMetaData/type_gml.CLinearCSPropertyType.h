#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearCSPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearCSPropertyType



namespace gie
{

namespace gml
{	

class CLinearCSPropertyType : public TypeBase
{
public:
	gie_EXPORT CLinearCSPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLinearCSPropertyType(CLinearCSPropertyType const& init);
	void operator=(CLinearCSPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLinearCSPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CLinearCSPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CLinearCSType, _altova_mi_gml_altova_CLinearCSPropertyType_altova_LinearCS> LinearCS;
	struct LinearCS { typedef Iterator<gml::CLinearCSType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearCSPropertyType
