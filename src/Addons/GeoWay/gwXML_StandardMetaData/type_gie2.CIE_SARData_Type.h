#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARData_Type

#include "type_gie2.CIE_ActiveMWData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_SARData_Type : public ::gie::gie2::CIE_ActiveMWData_Type
{
public:
	gie_EXPORT CIE_SARData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SARData_Type(CIE_SARData_Type const& init);
	void operator=(CIE_SARData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SARData_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARData_Type_altova_farRangeIncidenceAngle> farRangeIncidenceAngle;
	struct farRangeIncidenceAngle { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARData_Type_altova_nearRangeIncidenceAngle> nearRangeIncidenceAngle;
	struct nearRangeIncidenceAngle { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gie2::CIE_SARImagingModeCode_PropertyType, _altova_mi_gie2_altova_CIE_SARData_Type_altova_sarImagingMode> sarImagingMode;
	struct sarImagingMode { typedef Iterator<gie2::CIE_SARImagingModeCode_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_SARData_Type_altova_waveLength> waveLength;
	struct waveLength { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_SARData_Type_altova_sarModeDescription> sarModeDescription;
	struct sarModeDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARData_Type
