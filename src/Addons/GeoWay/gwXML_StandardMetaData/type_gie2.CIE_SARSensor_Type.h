#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARSensor_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARSensor_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_SARSensor_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_SARSensor_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SARSensor_Type(CIE_SARSensor_Type const& init);
	void operator=(CIE_SARSensor_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SARSensor_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_azimuthBandwidth> azimuthBandwidth;
	struct azimuthBandwidth { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gie2::CIE_SARDopplerCentroidParameter_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_dopplerCentroid> dopplerCentroid;
	struct dopplerCentroid { typedef Iterator<gie2::CIE_SARDopplerCentroidParameter_PropertyType> iterator; };
	MemberElement<gcv::CTime_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_oneWayTimeToFirstRangePixel> oneWayTimeToFirstRangePixel;
	struct oneWayTimeToFirstRangePixel { typedef Iterator<gcv::CTime_PropertyType> iterator; };
	MemberElement<gie2::CIE_OrbitParameter_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_orbitParameter> orbitParameter;
	struct orbitParameter { typedef Iterator<gie2::CIE_OrbitParameter_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_pulseRepititionFrequency> pulseRepititionFrequency;
	struct pulseRepititionFrequency { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_rangeBandwidth> rangeBandwidth;
	struct rangeBandwidth { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_rangeSamplingRate> rangeSamplingRate;
	struct rangeSamplingRate { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gie2_altova_CIE_SARSensor_Type_altova_timeOfFirstAzimuthLine> timeOfFirstAzimuthLine;
	struct timeOfFirstAzimuthLine { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARSensor_Type
