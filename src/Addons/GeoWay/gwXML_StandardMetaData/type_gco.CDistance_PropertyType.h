#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDistance_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDistance_PropertyType



namespace gie
{

namespace gco
{	

class CDistance_PropertyType : public TypeBase
{
public:
	gie_EXPORT CDistance_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDistance_PropertyType(CDistance_PropertyType const& init);
	void operator=(CDistance_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CDistance_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CDistance_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CLengthType, _altova_mi_gco_altova_CDistance_PropertyType_altova_Distance> Distance;
	struct Distance { typedef Iterator<gml::CLengthType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDistance_PropertyType
