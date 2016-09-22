#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridEnvelopeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridEnvelopeType



namespace gie
{

namespace gml
{	

class CGridEnvelopeType : public TypeBase
{
public:
	gie_EXPORT CGridEnvelopeType(xercesc::DOMNode* const& init);
	gie_EXPORT CGridEnvelopeType(CGridEnvelopeType const& init);
	void operator=(CGridEnvelopeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGridEnvelopeType); }
	MemberElement<gml::CintegerListType, _altova_mi_gml_altova_CGridEnvelopeType_altova_low> low;
	struct low { typedef Iterator<gml::CintegerListType> iterator; };
	MemberElement<gml::CintegerListType, _altova_mi_gml_altova_CGridEnvelopeType_altova_high> high;
	struct high { typedef Iterator<gml::CintegerListType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridEnvelopeType
