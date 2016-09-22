#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CTypeName_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CTypeName_PropertyType



namespace gie
{

namespace gco
{	

class CTypeName_PropertyType : public TypeBase
{
public:
	gie_EXPORT CTypeName_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTypeName_PropertyType(CTypeName_PropertyType const& init);
	void operator=(CTypeName_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CTypeName_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CTypeName_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CTypeName_Type, _altova_mi_gco_altova_CTypeName_PropertyType_altova_TypeName2> TypeName2;
	struct TypeName2 { typedef Iterator<gco::CTypeName_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CTypeName_PropertyType
