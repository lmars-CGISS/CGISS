#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RequestedDate_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RequestedDate_PropertyType



namespace gie
{

namespace gmi
{	

class CMI_RequestedDate_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMI_RequestedDate_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_RequestedDate_PropertyType(CMI_RequestedDate_PropertyType const& init);
	void operator=(CMI_RequestedDate_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_RequestedDate_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmi::CMI_RequestedDate_Type, _altova_mi_gmi_altova_CMI_RequestedDate_PropertyType_altova_MI_RequestedDate> MI_RequestedDate;
	struct MI_RequestedDate { typedef Iterator<gmi::CMI_RequestedDate_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RequestedDate_PropertyType