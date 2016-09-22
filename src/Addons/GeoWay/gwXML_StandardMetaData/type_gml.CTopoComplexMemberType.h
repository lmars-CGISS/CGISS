#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoComplexMemberType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoComplexMemberType



namespace gie
{

namespace gml
{	

class CTopoComplexMemberType : public TypeBase
{
public:
	gie_EXPORT CTopoComplexMemberType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoComplexMemberType(CTopoComplexMemberType const& init);
	void operator=(CTopoComplexMemberType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoComplexMemberType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexMemberType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CTopoComplexType, _altova_mi_gml_altova_CTopoComplexMemberType_altova_TopoComplex> TopoComplex;
	struct TopoComplex { typedef Iterator<gml::CTopoComplexType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoComplexMemberType
