#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWBand_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWBand_PropertyType



namespace gie
{

namespace gie2
{	

class CIE_PMWBand_PropertyType : public TypeBase
{
public:
	gie_EXPORT CIE_PMWBand_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_PMWBand_PropertyType(CIE_PMWBand_PropertyType const& init);
	void operator=(CIE_PMWBand_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_PMWBand_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gie2::CIE_PMWBand_Type, _altova_mi_gie2_altova_CIE_PMWBand_PropertyType_altova_IE_PMWBand> IE_PMWBand;
	struct IE_PMWBand { typedef Iterator<gie2::CIE_PMWBand_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWBand_PropertyType
