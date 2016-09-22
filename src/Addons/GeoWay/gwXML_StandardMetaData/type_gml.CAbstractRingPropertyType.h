#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractRingPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractRingPropertyType



namespace gie
{

namespace gml
{	

class CAbstractRingPropertyType : public TypeBase
{
public:
	gie_EXPORT CAbstractRingPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractRingPropertyType(CAbstractRingPropertyType const& init);
	void operator=(CAbstractRingPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractRingPropertyType); }
	MemberElement<gml::CLinearRingType, _altova_mi_gml_altova_CAbstractRingPropertyType_altova_LinearRing> LinearRing;
	struct LinearRing { typedef Iterator<gml::CLinearRingType> iterator; };
	MemberElement<gml::CRingType, _altova_mi_gml_altova_CAbstractRingPropertyType_altova_Ring> Ring;
	struct Ring { typedef Iterator<gml::CRingType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractRingPropertyType
