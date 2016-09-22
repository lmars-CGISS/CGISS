#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePeriodType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePeriodType

#include "type_gml.CAbstractTimeGeometricPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CTimePeriodType : public ::gie::gml::CAbstractTimeGeometricPrimitiveType
{
public:
	gie_EXPORT CTimePeriodType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimePeriodType(CTimePeriodType const& init);
	void operator=(CTimePeriodType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimePeriodType); }
	MemberElement<gml::CTimePositionType, _altova_mi_gml_altova_CTimePeriodType_altova_beginPosition> beginPosition;
	struct beginPosition { typedef Iterator<gml::CTimePositionType> iterator; };
	MemberElement<gml::CTimeInstantPropertyType, _altova_mi_gml_altova_CTimePeriodType_altova_begin> begin;
	struct begin { typedef Iterator<gml::CTimeInstantPropertyType> iterator; };
	MemberElement<gml::CTimePositionType, _altova_mi_gml_altova_CTimePeriodType_altova_endPosition> endPosition;
	struct endPosition { typedef Iterator<gml::CTimePositionType> iterator; };
	MemberElement<gml::CTimeInstantPropertyType, _altova_mi_gml_altova_CTimePeriodType_altova_end> end;
	struct end { typedef Iterator<gml::CTimeInstantPropertyType> iterator; };
	MemberElement<xs::CdurationType, _altova_mi_gml_altova_CTimePeriodType_altova_duration> duration;
	struct duration { typedef Iterator<xs::CdurationType> iterator; };
	MemberElement<gml::CTimeIntervalLengthType, _altova_mi_gml_altova_CTimePeriodType_altova_timeInterval> timeInterval;
	struct timeInterval { typedef Iterator<gml::CTimeIntervalLengthType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePeriodType
