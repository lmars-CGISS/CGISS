#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_RadiometerData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_RadiometerData_Type

#include "type_gie2.CIE_PassiveMWData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_RadiometerData_Type : public ::gie::gie2::CIE_PassiveMWData_Type
{
public:
	gie_EXPORT CIE_RadiometerData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_RadiometerData_Type(CIE_RadiometerData_Type const& init);
	void operator=(CIE_RadiometerData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_RadiometerData_Type); }
	MemberElement<gie2::CIE_PMWScanningModeCode_PropertyType, _altova_mi_gie2_altova_CIE_RadiometerData_Type_altova_scanningMode> scanningMode;
	struct scanningMode { typedef Iterator<gie2::CIE_PMWScanningModeCode_PropertyType> iterator; };
	MemberElement<gie2::CIE_PMWBand_PropertyType, _altova_mi_gie2_altova_CIE_RadiometerData_Type_altova_PMWBand> PMWBand;
	struct PMWBand { typedef Iterator<gie2::CIE_PMWBand_PropertyType> iterator; };
	MemberElement<gie2::CIE_PMWApertureTypeCode_PropertyType, _altova_mi_gie2_altova_CIE_RadiometerData_Type_altova_apertureType> apertureType;
	struct apertureType { typedef Iterator<gie2::CIE_PMWApertureTypeCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_RadiometerData_Type
