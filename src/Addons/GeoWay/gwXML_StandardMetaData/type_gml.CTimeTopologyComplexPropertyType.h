#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyComplexPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyComplexPropertyType



namespace gie
{

namespace gml
{	

class CTimeTopologyComplexPropertyType : public TypeBase
{
public:
	gie_EXPORT CTimeTopologyComplexPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeTopologyComplexPropertyType(CTimeTopologyComplexPropertyType const& init);
	void operator=(CTimeTopologyComplexPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeTopologyComplexPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CTimeTopologyComplexType, _altova_mi_gml_altova_CTimeTopologyComplexPropertyType_altova_TimeTopologyComplex> TimeTopologyComplex;
	struct TimeTopologyComplex { typedef Iterator<gml::CTimeTopologyComplexType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyComplexPropertyType
