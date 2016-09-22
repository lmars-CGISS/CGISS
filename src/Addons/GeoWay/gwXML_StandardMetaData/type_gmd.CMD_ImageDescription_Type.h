#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ImageDescription_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ImageDescription_Type

#include "type_gmd.CMD_CoverageDescription_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_ImageDescription_Type : public ::gie::gmd::CMD_CoverageDescription_Type
{
public:
	gie_EXPORT CMD_ImageDescription_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_ImageDescription_Type(CMD_ImageDescription_Type const& init);
	void operator=(CMD_ImageDescription_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_ImageDescription_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_illuminationElevationAngle> illuminationElevationAngle;
	struct illuminationElevationAngle { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_illuminationAzimuthAngle> illuminationAzimuthAngle;
	struct illuminationAzimuthAngle { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gmd::CMD_ImagingConditionCode_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_imagingCondition> imagingCondition;
	struct imagingCondition { typedef Iterator<gmd::CMD_ImagingConditionCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_imageQualityCode> imageQualityCode;
	struct imageQualityCode { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_cloudCoverPercentage> cloudCoverPercentage;
	struct cloudCoverPercentage { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_processingLevelCode> processingLevelCode;
	struct processingLevelCode { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_compressionGenerationQuantity> compressionGenerationQuantity;
	struct compressionGenerationQuantity { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_triangulationIndicator> triangulationIndicator;
	struct triangulationIndicator { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_radiometricCalibrationDataAvailability> radiometricCalibrationDataAvailability;
	struct radiometricCalibrationDataAvailability { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_cameraCalibrationInformationAvailability> cameraCalibrationInformationAvailability;
	struct cameraCalibrationInformationAvailability { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_filmDistortionInformationAvailability> filmDistortionInformationAvailability;
	struct filmDistortionInformationAvailability { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CMD_ImageDescription_Type_altova_lensDistortionInformationAvailability> lensDistortionInformationAvailability;
	struct lensDistortionInformationAvailability { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ImageDescription_Type
