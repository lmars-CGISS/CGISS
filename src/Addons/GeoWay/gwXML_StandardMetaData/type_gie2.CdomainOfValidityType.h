#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CdomainOfValidityType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CdomainOfValidityType



namespace gie
{

namespace gie2
{	

class CdomainOfValidityType : public TypeBase
{
public:
	gie_EXPORT CdomainOfValidityType(xercesc::DOMNode* const& init);
	gie_EXPORT CdomainOfValidityType(CdomainOfValidityType const& init);
	void operator=(CdomainOfValidityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CdomainOfValidityType); }

	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gie2_altova_CdomainOfValidityType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gmd::CEX_Extent_Type, _altova_mi_gie2_altova_CdomainOfValidityType_altova_EX_Extent> EX_Extent;
	struct EX_Extent { typedef Iterator<gmd::CEX_Extent_Type> iterator; };
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CdomainOfValidityType
