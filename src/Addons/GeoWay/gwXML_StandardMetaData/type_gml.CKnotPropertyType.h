#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CKnotPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CKnotPropertyType



namespace gie
{

namespace gml
{	

class CKnotPropertyType : public TypeBase
{
public:
	gie_EXPORT CKnotPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CKnotPropertyType(CKnotPropertyType const& init);
	void operator=(CKnotPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CKnotPropertyType); }
	MemberElement<gml::CKnotType, _altova_mi_gml_altova_CKnotPropertyType_altova_Knot> Knot;
	struct Knot { typedef Iterator<gml::CKnotType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CKnotPropertyType
