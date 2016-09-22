#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridLimitsType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridLimitsType



namespace gie
{

namespace gml
{	

class CGridLimitsType : public TypeBase
{
public:
	gie_EXPORT CGridLimitsType(xercesc::DOMNode* const& init);
	gie_EXPORT CGridLimitsType(CGridLimitsType const& init);
	void operator=(CGridLimitsType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGridLimitsType); }
	MemberElement<gml::CGridEnvelopeType, _altova_mi_gml_altova_CGridLimitsType_altova_GridEnvelope> GridEnvelope;
	struct GridEnvelope { typedef Iterator<gml::CGridEnvelopeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridLimitsType
