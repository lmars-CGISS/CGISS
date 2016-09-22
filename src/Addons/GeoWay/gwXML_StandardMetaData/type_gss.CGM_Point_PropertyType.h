#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gss_ALTOVA_CGM_Point_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gss_ALTOVA_CGM_Point_PropertyType



namespace gie
{

namespace gss
{	

class CGM_Point_PropertyType : public TypeBase
{
public:
	gie_EXPORT CGM_Point_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CGM_Point_PropertyType(CGM_Point_PropertyType const& init);
	void operator=(CGM_Point_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gss_altova_CGM_Point_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gss_altova_CGM_Point_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CPointType, _altova_mi_gss_altova_CGM_Point_PropertyType_altova_Point> Point;
	struct Point { typedef Iterator<gml::CPointType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gss

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gss_ALTOVA_CGM_Point_PropertyType
