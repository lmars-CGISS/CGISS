#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_Imagery_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_Imagery_Type

#include "type_gie2.CAbstractIE_ImageryandGriddedData_Type.h"


namespace gie
{

namespace gie2
{	

class CAbstractIE_Imagery_Type : public ::gie::gie2::CAbstractIE_ImageryandGriddedData_Type
{
public:
	gie_EXPORT CAbstractIE_Imagery_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractIE_Imagery_Type(CAbstractIE_Imagery_Type const& init);
	void operator=(CAbstractIE_Imagery_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CAbstractIE_Imagery_Type); }
	MemberElement<gcv::CTM_Period_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_acquisitionTime> acquisitionTime;
	struct acquisitionTime { typedef Iterator<gcv::CTM_Period_PropertyType> iterator; };
	MemberElement<gmd::CMD_ImageDescription_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_imageDescription> imageDescription;
	struct imageDescription { typedef Iterator<gmd::CMD_ImageDescription_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_isMosaic> isMosaic;
	struct isMosaic { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_numberofBands> numberofBands;
	struct numberofBands { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gie2::CIE_ProcessingActionCode_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_processingAction> processingAction;
	struct processingAction { typedef Iterator<gie2::CIE_ProcessingActionCode_PropertyType> iterator; };
	MemberElement<gie2::CIE_RadiometricCalibrationTypeCode_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_radiometricCalibrationType> radiometricCalibrationType;
	struct radiometricCalibrationType { typedef Iterator<gie2::CIE_RadiometricCalibrationTypeCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_sensorCalibrationValidation> sensorCalibrationValidation;
	struct sensorCalibrationValidation { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmi::CMI_Platform_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_platformInfo> platformInfo;
	struct platformInfo { typedef Iterator<gmi::CMI_Platform_PropertyType> iterator; };
	MemberElement<gmi::CMI_Instrument_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_sensorInfo> sensorInfo;
	struct sensorInfo { typedef Iterator<gmi::CMI_Instrument_PropertyType> iterator; };
	MemberElement<gmi::CMI_Band_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_bandinformation> bandinformation;
	struct bandinformation { typedef Iterator<gmi::CMI_Band_PropertyType> iterator; };
	MemberElement<gie2::CIE_Imagery_PropertyType, _altova_mi_gie2_altova_CAbstractIE_Imagery_Type_altova_masaicInfo> masaicInfo;
	struct mosaicInfo { typedef Iterator<gie2::CIE_MosaicElement_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_Imagery_Type
