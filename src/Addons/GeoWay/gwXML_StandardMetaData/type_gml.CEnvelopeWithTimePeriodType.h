#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEnvelopeWithTimePeriodType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEnvelopeWithTimePeriodType

#include "type_gml.CEnvelopeType.h"


namespace gie
{

namespace gml
{	

class CEnvelopeWithTimePeriodType : public ::gie::gml::CEnvelopeType
{
public:
	gie_EXPORT CEnvelopeWithTimePeriodType(xercesc::DOMNode* const& init);
	gie_EXPORT CEnvelopeWithTimePeriodType(CEnvelopeWithTimePeriodType const& init);
	void operator=(CEnvelopeWithTimePeriodType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CEnvelopeWithTimePeriodType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CEnvelopeWithTimePeriodType_altova_frame, 0, 0> frame;	// frame CanyURI
	MemberElement<gml::CTimePositionType, _altova_mi_gml_altova_CEnvelopeWithTimePeriodType_altova_beginPosition> beginPosition;
	struct beginPosition { typedef Iterator<gml::CTimePositionType> iterator; };
	MemberElement<gml::CTimePositionType, _altova_mi_gml_altova_CEnvelopeWithTimePeriodType_altova_endPosition> endPosition;
	struct endPosition { typedef Iterator<gml::CTimePositionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEnvelopeWithTimePeriodType
