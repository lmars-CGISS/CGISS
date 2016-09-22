#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRingPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRingPropertyType



namespace gie
{

namespace gml
{	

class CRingPropertyType : public TypeBase
{
public:
	gie_EXPORT CRingPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CRingPropertyType(CRingPropertyType const& init);
	void operator=(CRingPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRingPropertyType); }
	MemberElement<gml::CRingType, _altova_mi_gml_altova_CRingPropertyType_altova_Ring> Ring;
	struct Ring { typedef Iterator<gml::CRingType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRingPropertyType
