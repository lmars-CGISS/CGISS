#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARAmplitudeData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARAmplitudeData_Type

#include "type_gie2.CIE_SARData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_SARAmplitudeData_Type : public ::gie::gie2::CIE_SARData_Type
{
public:
	gie_EXPORT CIE_SARAmplitudeData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SARAmplitudeData_Type(CIE_SARAmplitudeData_Type const& init);
	void operator=(CIE_SARAmplitudeData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SARAmplitudeData_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARAmplitudeData_Type_altova_calibrationFactor> calibrationFactor;
	struct calibrationFactor { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_SARAmplitudeData_Type_altova_looksInAzimuth> looksInAzimuth;
	struct looksInAzimuth { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_SARAmplitudeData_Type_altova_looksInRange> looksInRange;
	struct looksInRange { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gie2::CIE_SARSensor_PropertyType, _altova_mi_gie2_altova_CIE_SARAmplitudeData_Type_altova_sarSensor> sarSensor;
	struct sarSensor { typedef Iterator<gie2::CIE_SARSensor_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARAmplitudeData_Type
