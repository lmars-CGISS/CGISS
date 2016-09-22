#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_OpticalImage_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_OpticalImage_Type

#include "type_gie2.CAbstractIE_Imagery_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_OpticalImage_Type : public ::gie::gie2::CAbstractIE_Imagery_Type
{
public:
	gie_EXPORT CIE_OpticalImage_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_OpticalImage_Type(CIE_OpticalImage_Type const& init);
	void operator=(CIE_OpticalImage_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_OpticalImage_Type); }
	MemberElement<gie2::CIE_OpticalImageTypeCode_PropertyType, _altova_mi_gie2_altova_CIE_OpticalImage_Type_altova_opticalImageType> opticalImageType;
	struct opticalImageType { typedef Iterator<gie2::CIE_OpticalImageTypeCode_PropertyType> iterator; };
	MemberElement<gie2::CIE_OpticalSensorTypeCode_PropertyType, _altova_mi_gie2_altova_CIE_OpticalImage_Type_altova_opticalSensorType> opticalSensorType;
	struct opticalSensorType { typedef Iterator<gie2::CIE_OpticalSensorTypeCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_OpticalImage_Type
