#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CInteger_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CInteger_PropertyType



namespace gie
{

namespace gco
{	

class CInteger_PropertyType : public TypeBase
{
public:
	gie_EXPORT CInteger_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CInteger_PropertyType(CInteger_PropertyType const& init);
	void operator=(CInteger_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CInteger_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CInteger_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<xs::CintegerType, _altova_mi_gco_altova_CInteger_PropertyType_altova_Integer> Integer;
	struct Integer { typedef Iterator<xs::CintegerType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CInteger_PropertyType
