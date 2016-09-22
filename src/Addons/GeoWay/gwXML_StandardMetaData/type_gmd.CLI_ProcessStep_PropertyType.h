#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_ProcessStep_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_ProcessStep_PropertyType



namespace gie
{

namespace gmd
{	

class CLI_ProcessStep_PropertyType : public TypeBase
{
public:
	gie_EXPORT CLI_ProcessStep_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLI_ProcessStep_PropertyType(CLI_ProcessStep_PropertyType const& init);
	void operator=(CLI_ProcessStep_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CLI_ProcessStep_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmd::CLI_ProcessStep_Type, _altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_LI_ProcessStep> LI_ProcessStep;
	struct LI_ProcessStep { typedef Iterator<gmd::CLI_ProcessStep_Type> iterator; };
	MemberElement<gmi::CLE_ProcessStep_Type, _altova_mi_gmd_altova_CLI_ProcessStep_PropertyType_altova_LE_ProcessStep> LE_ProcessStep;
	struct LE_ProcessStep { typedef Iterator<gmi::CLE_ProcessStep_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_ProcessStep_PropertyType
