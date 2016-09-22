#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CBinary_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CBinary_PropertyType



namespace gie
{

namespace gco
{	

class CBinary_PropertyType : public TypeBase
{
public:
	gie_EXPORT CBinary_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CBinary_PropertyType(CBinary_PropertyType const& init);
	void operator=(CBinary_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CBinary_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CBinary_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CBinary_Type, _altova_mi_gco_altova_CBinary_PropertyType_altova_Binary> Binary;
	struct Binary { typedef Iterator<gco::CBinary_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CBinary_PropertyType
