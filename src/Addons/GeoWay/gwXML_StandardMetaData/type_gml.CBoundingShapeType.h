#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBoundingShapeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBoundingShapeType



namespace gie
{

namespace gml
{	

class CBoundingShapeType : public TypeBase
{
public:
	gie_EXPORT CBoundingShapeType(xercesc::DOMNode* const& init);
	gie_EXPORT CBoundingShapeType(CBoundingShapeType const& init);
	void operator=(CBoundingShapeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CBoundingShapeType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CBoundingShapeType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CEnvelopeType, _altova_mi_gml_altova_CBoundingShapeType_altova_Envelope> Envelope;
	struct Envelope { typedef Iterator<gml::CEnvelopeType> iterator; };
	MemberElement<gml::CEnvelopeWithTimePeriodType, _altova_mi_gml_altova_CBoundingShapeType_altova_EnvelopeWithTimePeriod> EnvelopeWithTimePeriod;
	struct EnvelopeWithTimePeriod { typedef Iterator<gml::CEnvelopeWithTimePeriodType> iterator; };
	MemberElement<gml::CNilReasonTypeType, _altova_mi_gml_altova_CBoundingShapeType_altova_Null> Null;
	struct Null { typedef Iterator<gml::CNilReasonTypeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBoundingShapeType
