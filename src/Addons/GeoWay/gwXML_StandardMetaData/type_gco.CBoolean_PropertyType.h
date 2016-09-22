#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CBoolean_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CBoolean_PropertyType



namespace gie
{

namespace gco
{	

class CBoolean_PropertyType : public TypeBase
{
public:
	gie_EXPORT CBoolean_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CBoolean_PropertyType(CBoolean_PropertyType const& init);
	void operator=(CBoolean_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CBoolean_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CBoolean_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<xs::CbooleanType, _altova_mi_gco_altova_CBoolean_PropertyType_altova_Boolean> Boolean;
	struct Boolean { typedef Iterator<xs::CbooleanType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CBoolean_PropertyType
