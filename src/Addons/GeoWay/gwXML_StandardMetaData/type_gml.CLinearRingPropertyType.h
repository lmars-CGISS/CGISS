#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearRingPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearRingPropertyType



namespace gie
{

namespace gml
{	

class CLinearRingPropertyType : public TypeBase
{
public:
	gie_EXPORT CLinearRingPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLinearRingPropertyType(CLinearRingPropertyType const& init);
	void operator=(CLinearRingPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLinearRingPropertyType); }
	MemberElement<gml::CLinearRingType, _altova_mi_gml_altova_CLinearRingPropertyType_altova_LinearRing> LinearRing;
	struct LinearRing { typedef Iterator<gml::CLinearRingType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearRingPropertyType
