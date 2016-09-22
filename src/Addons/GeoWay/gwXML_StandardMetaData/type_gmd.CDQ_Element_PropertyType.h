#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_Element_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_Element_PropertyType



namespace gie
{

namespace gmd
{	

class CDQ_Element_PropertyType : public TypeBase
{
public:
	gie_EXPORT CDQ_Element_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDQ_Element_PropertyType(CDQ_Element_PropertyType const& init);
	void operator=(CDQ_Element_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDQ_Element_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmd::CDQ_AbsoluteExternalPositionalAccuracy_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_AbsoluteExternalPositionalAccuracy> DQ_AbsoluteExternalPositionalAccuracy;
	struct DQ_AbsoluteExternalPositionalAccuracy { typedef Iterator<gmd::CDQ_AbsoluteExternalPositionalAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_AccuracyOfATimeMeasurement_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_AccuracyOfATimeMeasurement> DQ_AccuracyOfATimeMeasurement;
	struct DQ_AccuracyOfATimeMeasurement { typedef Iterator<gmd::CDQ_AccuracyOfATimeMeasurement_Type> iterator; };
	MemberElement<gmd::CDQ_CompletenessCommission_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_CompletenessCommission> DQ_CompletenessCommission;
	struct DQ_CompletenessCommission { typedef Iterator<gmd::CDQ_CompletenessCommission_Type> iterator; };
	MemberElement<gmd::CDQ_CompletenessOmission_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_CompletenessOmission> DQ_CompletenessOmission;
	struct DQ_CompletenessOmission { typedef Iterator<gmd::CDQ_CompletenessOmission_Type> iterator; };
	MemberElement<gmd::CDQ_ConceptualConsistency_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_ConceptualConsistency> DQ_ConceptualConsistency;
	struct DQ_ConceptualConsistency { typedef Iterator<gmd::CDQ_ConceptualConsistency_Type> iterator; };
	MemberElement<gmd::CDQ_DomainConsistency_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_DomainConsistency> DQ_DomainConsistency;
	struct DQ_DomainConsistency { typedef Iterator<gmd::CDQ_DomainConsistency_Type> iterator; };
	MemberElement<gmd::CDQ_FormatConsistency_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_FormatConsistency> DQ_FormatConsistency;
	struct DQ_FormatConsistency { typedef Iterator<gmd::CDQ_FormatConsistency_Type> iterator; };
	MemberElement<gmd::CDQ_GriddedDataPositionalAccuracy_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_GriddedDataPositionalAccuracy> DQ_GriddedDataPositionalAccuracy;
	struct DQ_GriddedDataPositionalAccuracy { typedef Iterator<gmd::CDQ_GriddedDataPositionalAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_NonQuantitativeAttributeAccuracy_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_NonQuantitativeAttributeAccuracy> DQ_NonQuantitativeAttributeAccuracy;
	struct DQ_NonQuantitativeAttributeAccuracy { typedef Iterator<gmd::CDQ_NonQuantitativeAttributeAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_QuantitativeAttributeAccuracy_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_QuantitativeAttributeAccuracy> DQ_QuantitativeAttributeAccuracy;
	struct DQ_QuantitativeAttributeAccuracy { typedef Iterator<gmd::CDQ_QuantitativeAttributeAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_RelativeInternalPositionalAccuracy_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_RelativeInternalPositionalAccuracy> DQ_RelativeInternalPositionalAccuracy;
	struct DQ_RelativeInternalPositionalAccuracy { typedef Iterator<gmd::CDQ_RelativeInternalPositionalAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_TemporalConsistency_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_TemporalConsistency> DQ_TemporalConsistency;
	struct DQ_TemporalConsistency { typedef Iterator<gmd::CDQ_TemporalConsistency_Type> iterator; };
	MemberElement<gmd::CDQ_TemporalValidity_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_TemporalValidity> DQ_TemporalValidity;
	struct DQ_TemporalValidity { typedef Iterator<gmd::CDQ_TemporalValidity_Type> iterator; };
	MemberElement<gmd::CDQ_ThematicClassificationCorrectness_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_ThematicClassificationCorrectness> DQ_ThematicClassificationCorrectness;
	struct DQ_ThematicClassificationCorrectness { typedef Iterator<gmd::CDQ_ThematicClassificationCorrectness_Type> iterator; };
	MemberElement<gmd::CDQ_TopologicalConsistency_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_DQ_TopologicalConsistency> DQ_TopologicalConsistency;
	struct DQ_TopologicalConsistency { typedef Iterator<gmd::CDQ_TopologicalConsistency_Type> iterator; };
	MemberElement<gmi::CQE_Usability_Type, _altova_mi_gmd_altova_CDQ_Element_PropertyType_altova_QE_Usability> QE_Usability;
	struct QE_Usability { typedef Iterator<gmi::CQE_Usability_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_Element_PropertyType
