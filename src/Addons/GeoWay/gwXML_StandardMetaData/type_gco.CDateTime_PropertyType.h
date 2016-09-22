#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDateTime_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDateTime_PropertyType



namespace gie
{

namespace gco
{	

class CDateTime_PropertyType : public TypeBase
{
public:
	gie_EXPORT CDateTime_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDateTime_PropertyType(CDateTime_PropertyType const& init);
	void operator=(CDateTime_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CDateTime_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CDateTime_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<xs::CdateTimeType, _altova_mi_gco_altova_CDateTime_PropertyType_altova_DateTime> DateTime;
	struct DateTime { typedef Iterator<xs::CdateTimeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDateTime_PropertyType
