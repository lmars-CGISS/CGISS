#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_EnvironmentalRecord_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_EnvironmentalRecord_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_EnvironmentalRecord_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_EnvironmentalRecord_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_EnvironmentalRecord_Type(CMI_EnvironmentalRecord_Type const& init);
	void operator=(CMI_EnvironmentalRecord_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_EnvironmentalRecord_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmi_altova_CMI_EnvironmentalRecord_Type_altova_averageAirTemperature> averageAirTemperature;
	struct averageAirTemperature { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmi_altova_CMI_EnvironmentalRecord_Type_altova_maxRelativeHumidity> maxRelativeHumidity;
	struct maxRelativeHumidity { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmi_altova_CMI_EnvironmentalRecord_Type_altova_maxAltitude> maxAltitude;
	struct maxAltitude { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CMI_EnvironmentalRecord_Type_altova_meterologicalConditions> meterologicalConditions;
	struct meterologicalConditions { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_EnvironmentalRecord_Type
