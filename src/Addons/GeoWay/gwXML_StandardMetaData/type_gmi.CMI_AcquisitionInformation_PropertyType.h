#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_AcquisitionInformation_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_AcquisitionInformation_PropertyType



namespace gie
{

namespace gmi
{	

class CMI_AcquisitionInformation_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMI_AcquisitionInformation_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_AcquisitionInformation_PropertyType(CMI_AcquisitionInformation_PropertyType const& init);
	void operator=(CMI_AcquisitionInformation_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_AcquisitionInformation_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmi::CMI_AcquisitionInformation_Type, _altova_mi_gmi_altova_CMI_AcquisitionInformation_PropertyType_altova_MI_AcquisitionInformation> MI_AcquisitionInformation;
	struct MI_AcquisitionInformation { typedef Iterator<gmi::CMI_AcquisitionInformation_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_AcquisitionInformation_PropertyType
