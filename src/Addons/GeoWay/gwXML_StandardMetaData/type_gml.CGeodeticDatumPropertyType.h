#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodeticDatumPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodeticDatumPropertyType



namespace gie
{

namespace gml
{	

class CGeodeticDatumPropertyType : public TypeBase
{
public:
	gie_EXPORT CGeodeticDatumPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeodeticDatumPropertyType(CGeodeticDatumPropertyType const& init);
	void operator=(CGeodeticDatumPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeodeticDatumPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CGeodeticDatumType, _altova_mi_gml_altova_CGeodeticDatumPropertyType_altova_GeodeticDatum> GeodeticDatum;
	struct GeodeticDatum { typedef Iterator<gml::CGeodeticDatumType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodeticDatumPropertyType
