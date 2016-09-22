#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedTopoSolidPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedTopoSolidPropertyType



namespace gie
{

namespace gml
{	

class CDirectedTopoSolidPropertyType : public TypeBase
{
public:
	gie_EXPORT CDirectedTopoSolidPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectedTopoSolidPropertyType(CDirectedTopoSolidPropertyType const& init);
	void operator=(CDirectedTopoSolidPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectedTopoSolidPropertyType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_orientation, 0, 2> orientation;	// orientation CSignType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CTopoSolidType, _altova_mi_gml_altova_CDirectedTopoSolidPropertyType_altova_TopoSolid> TopoSolid;
	struct TopoSolid { typedef Iterator<gml::CTopoSolidType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectedTopoSolidPropertyType
