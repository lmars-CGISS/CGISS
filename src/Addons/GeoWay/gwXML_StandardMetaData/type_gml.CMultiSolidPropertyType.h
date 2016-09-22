#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidPropertyType



namespace gie
{

namespace gml
{	

class CMultiSolidPropertyType : public TypeBase
{
public:
	gie_EXPORT CMultiSolidPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiSolidPropertyType(CMultiSolidPropertyType const& init);
	void operator=(CMultiSolidPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiSolidPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CMultiSolidPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CMultiSolidType, _altova_mi_gml_altova_CMultiSolidPropertyType_altova_MultiSolid> MultiSolid;
	struct MultiSolid { typedef Iterator<gml::CMultiSolidType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidPropertyType
