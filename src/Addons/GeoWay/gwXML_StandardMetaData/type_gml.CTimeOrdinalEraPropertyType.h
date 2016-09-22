#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalEraPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalEraPropertyType



namespace gie
{

namespace gml
{	

class CTimeOrdinalEraPropertyType : public TypeBase
{
public:
	gie_EXPORT CTimeOrdinalEraPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeOrdinalEraPropertyType(CTimeOrdinalEraPropertyType const& init);
	void operator=(CTimeOrdinalEraPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeOrdinalEraPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CTimeOrdinalEraType, _altova_mi_gml_altova_CTimeOrdinalEraPropertyType_altova_TimeOrdinalEra> TimeOrdinalEra;
	struct TimeOrdinalEra { typedef Iterator<gml::CTimeOrdinalEraType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeOrdinalEraPropertyType
