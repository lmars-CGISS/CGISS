#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CCharacterString_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CCharacterString_PropertyType



namespace gie
{

namespace gco
{	

class CCharacterString_PropertyType : public TypeBase
{
public:
	gie_EXPORT CCharacterString_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCharacterString_PropertyType(CCharacterString_PropertyType const& init);
	void operator=(CCharacterString_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CCharacterString_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CCharacterString_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<xs::CstringType, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CharacterString> CharacterString;
	struct CharacterString { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CI_DateTypeCode> CI_DateTypeCode;
	struct CI_DateTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CI_OnLineFunctionCode> CI_OnLineFunctionCode;
	struct CI_OnLineFunctionCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CI_PresentationFormCode> CI_PresentationFormCode;
	struct CI_PresentationFormCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CI_RoleCode> CI_RoleCode;
	struct CI_RoleCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_Country> Country;
	struct Country { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_DQ_EvaluationMethodTypeCode> DQ_EvaluationMethodTypeCode;
	struct DQ_EvaluationMethodTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_DS_AssociationTypeCode> DS_AssociationTypeCode;
	struct DS_AssociationTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_DS_InitiativeTypeCode> DS_InitiativeTypeCode;
	struct DS_InitiativeTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_LanguageCode> LanguageCode;
	struct LanguageCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gmd::CLocalisedCharacterString_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_LocalisedCharacterString> LocalisedCharacterString;
	struct LocalisedCharacterString { typedef Iterator<gmd::CLocalisedCharacterString_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_CellGeometryCode> MD_CellGeometryCode;
	struct MD_CellGeometryCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_CharacterSetCode> MD_CharacterSetCode;
	struct MD_CharacterSetCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_ClassificationCode> MD_ClassificationCode;
	struct MD_ClassificationCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_CoverageContentTypeCode> MD_CoverageContentTypeCode;
	struct MD_CoverageContentTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_DatatypeCode> MD_DatatypeCode;
	struct MD_DatatypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_DimensionNameTypeCode> MD_DimensionNameTypeCode;
	struct MD_DimensionNameTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_DistributionUnits> MD_DistributionUnits;
	struct MD_DistributionUnits { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_GeometricObjectTypeCode> MD_GeometricObjectTypeCode;
	struct MD_GeometricObjectTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_ImagingConditionCode> MD_ImagingConditionCode;
	struct MD_ImagingConditionCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_KeywordTypeCode> MD_KeywordTypeCode;
	struct MD_KeywordTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_MaintenanceFrequencyCode> MD_MaintenanceFrequencyCode;
	struct MD_MaintenanceFrequencyCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_MediumFormatCode> MD_MediumFormatCode;
	struct MD_MediumFormatCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_MediumNameCode> MD_MediumNameCode;
	struct MD_MediumNameCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gmd::CMD_ObligationCode_TypeType, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_ObligationCode> MD_ObligationCode;
	struct MD_ObligationCode { typedef Iterator<gmd::CMD_ObligationCode_TypeType> iterator; };
	MemberElement<gmd::CMD_PixelOrientationCode_TypeType, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_PixelOrientationCode> MD_PixelOrientationCode;
	struct MD_PixelOrientationCode { typedef Iterator<gmd::CMD_PixelOrientationCode_TypeType> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_ProgressCode> MD_ProgressCode;
	struct MD_ProgressCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_RestrictionCode> MD_RestrictionCode;
	struct MD_RestrictionCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_ScopeCode> MD_ScopeCode;
	struct MD_ScopeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_SpatialRepresentationTypeCode> MD_SpatialRepresentationTypeCode;
	struct MD_SpatialRepresentationTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gmd::CMD_TopicCategoryCode_TypeType, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_TopicCategoryCode> MD_TopicCategoryCode;
	struct MD_TopicCategoryCode { typedef Iterator<gmd::CMD_TopicCategoryCode_TypeType> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MD_TopologyLevelCode> MD_TopologyLevelCode;
	struct MD_TopologyLevelCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_BandDefinition> MI_BandDefinition;
	struct MI_BandDefinition { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_ContextCode> MI_ContextCode;
	struct MI_ContextCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_GeometryTypeCode> MI_GeometryTypeCode;
	struct MI_GeometryTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_ObjectiveTypeCode> MI_ObjectiveTypeCode;
	struct MI_ObjectiveTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_OperationTypeCode> MI_OperationTypeCode;
	struct MI_OperationTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_PolarisationOrientationCode> MI_PolarisationOrientationCode;
	struct MI_PolarisationOrientationCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_PriorityCode> MI_PriorityCode;
	struct MI_PriorityCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_SensorTypeCode> MI_SensorTypeCode;
	struct MI_SensorTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_SequenceCode> MI_SequenceCode;
	struct MI_SequenceCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_TransferFunctionTypeCode> MI_TransferFunctionTypeCode;
	struct MI_TransferFunctionTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_MI_TriggerCode> MI_TriggerCode;
	struct MI_TriggerCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CV_CommonPointRule> CV_CommonPointRule;
	struct CV_CommonPointRule { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_CV_InterpolationMethod> CV_InterpolationMethod;
	struct CV_InterpolationMethod { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_ChannelPropertyCode> IE_ChannelPropertyCode;
	struct IE_ChannelPropertyCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_CompressionSchemaCode> IE_CompressionSchemaCode;
	struct IE_CompressionSchemaCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_GeolocationSourceCode> IE_GeolocationSourceCode;
	struct IE_GeolocationSourceCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_GeometricCorrectionModelCode> IE_GeometricCorrectionModelCode;
	struct IE_GeometricCorrectionModelCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_LayerSequenceCode> IE_LayerSequenceCode;
	struct IE_LayerSequenceCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_OpticalImageTypeCode> IE_OpticalImageTypeCode;
	struct IE_OpticalImageTypeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_OpticalSensorTypeCode> IE_OpticalSensorTypeCode;
	struct IE_OpticalSensorTypeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_PMWApertureTypeCode> IE_PMWApertureTypeCode;
	struct IE_PMWApertureTypeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_PMWBandNameCode> IE_PMWBandNameCode;
	struct IE_PMWBandNameCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_PMWScanningModeCode> IE_PMWScanningModeCode;
	struct IE_PMWScanningModeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_ProcessingActionCode> IE_ProcessingActionCode;
	struct IE_ProcessingActionCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_RadiometricCalibrationTypeCode> IE_RadiometricCalibrationTypeCode;
	struct IE_RadiometricCalibrationTypeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_SARComplexLayerTypeCode> IE_SARComplexLayerTypeCode;
	struct IE_SARComplexLayerTypeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gco_altova_CCharacterString_PropertyType_altova_IE_SARImagingModeCode> IE_SARImagingModeCode;
	struct IE_SARImagingModeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CCharacterString_PropertyType
