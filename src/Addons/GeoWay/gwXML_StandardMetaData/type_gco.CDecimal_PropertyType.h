#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDecimal_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDecimal_PropertyType



namespace gie
{

namespace gco
{	

class CDecimal_PropertyType : public TypeBase
{
public:
	gie_EXPORT CDecimal_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDecimal_PropertyType(CDecimal_PropertyType const& init);
	void operator=(CDecimal_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CDecimal_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CDecimal_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<xs::CdecimalType, _altova_mi_gco_altova_CDecimal_PropertyType_altova_Decimal> Decimal;
	struct Decimal { typedef Iterator<xs::CdecimalType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDecimal_PropertyType
