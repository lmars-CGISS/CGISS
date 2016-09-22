#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicity_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicity_PropertyType



namespace gie
{

namespace gco
{	

class CMultiplicity_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMultiplicity_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiplicity_PropertyType(CMultiplicity_PropertyType const& init);
	void operator=(CMultiplicity_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CMultiplicity_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CMultiplicity_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CMultiplicity_Type, _altova_mi_gco_altova_CMultiplicity_PropertyType_altova_Multiplicity> Multiplicity;
	struct Multiplicity { typedef Iterator<gco::CMultiplicity_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMultiplicity_PropertyType
