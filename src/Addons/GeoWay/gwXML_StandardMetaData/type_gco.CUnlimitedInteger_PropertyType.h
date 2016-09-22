#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CUnlimitedInteger_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CUnlimitedInteger_PropertyType



namespace gie
{

namespace gco
{	

class CUnlimitedInteger_PropertyType : public TypeBase
{
public:
	gie_EXPORT CUnlimitedInteger_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CUnlimitedInteger_PropertyType(CUnlimitedInteger_PropertyType const& init);
	void operator=(CUnlimitedInteger_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CUnlimitedInteger_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CUnlimitedInteger_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CUnlimitedInteger_Type, _altova_mi_gco_altova_CUnlimitedInteger_PropertyType_altova_UnlimitedInteger> UnlimitedInteger;
	struct UnlimitedInteger { typedef Iterator<gco::CUnlimitedInteger_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CUnlimitedInteger_PropertyType
