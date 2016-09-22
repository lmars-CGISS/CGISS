#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CRS_Identifier_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CRS_Identifier_PropertyType



namespace gie
{

namespace gmd
{	

class CRS_Identifier_PropertyType : public TypeBase
{
public:
	gie_EXPORT CRS_Identifier_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CRS_Identifier_PropertyType(CRS_Identifier_PropertyType const& init);
	void operator=(CRS_Identifier_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CRS_Identifier_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmd::CRS_Identifier_Type, _altova_mi_gmd_altova_CRS_Identifier_PropertyType_altova_RS_Identifier> RS_Identifier;
	struct RS_Identifier { typedef Iterator<gmd::CRS_Identifier_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CRS_Identifier_PropertyType
