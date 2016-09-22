#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARComplexData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARComplexData_Type

#include "type_gie2.CIE_SARData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_SARComplexData_Type : public ::gie::gie2::CIE_SARData_Type
{
public:
	gie_EXPORT CIE_SARComplexData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SARComplexData_Type(CIE_SARComplexData_Type const& init);
	void operator=(CIE_SARComplexData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SARComplexData_Type); }
	MemberElement<gie2::CIE_SARComplexLayerTypeCode_PropertyType, _altova_mi_gie2_altova_CIE_SARComplexData_Type_altova_complexLayerTypes> complexLayerTypes;
	struct complexLayerTypes { typedef Iterator<gie2::CIE_SARComplexLayerTypeCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_SARComplexData_Type_altova_lineSpacing> lineSpacing;
	struct lineSpacing { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_SARComplexData_Type_altova_pixelSpacing> pixelSpacing;
	struct pixelSpacing { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gie2::CIE_SARSensor_PropertyType, _altova_mi_gie2_altova_CIE_SARComplexData_Type_altova_sarSensor> sarSensor;
	struct sarSensor { typedef Iterator<gie2::CIE_SARSensor_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARComplexData_Type
