#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CLength_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CLength_PropertyType



namespace gie
{

namespace gco
{	

class CLength_PropertyType : public TypeBase
{
public:
	gie_EXPORT CLength_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLength_PropertyType(CLength_PropertyType const& init);
	void operator=(CLength_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CLength_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CLength_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CLengthType, _altova_mi_gco_altova_CLength_PropertyType_altova_Length> Length;
	struct Length { typedef Iterator<gml::CLengthType> iterator; };
	MemberElement<gml::CLengthType, _altova_mi_gco_altova_CLength_PropertyType_altova_Distance> Distance;
	struct Distance { typedef Iterator<gml::CLengthType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CLength_PropertyType
