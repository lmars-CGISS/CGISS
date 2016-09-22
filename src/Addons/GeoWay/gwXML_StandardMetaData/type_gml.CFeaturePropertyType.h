#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeaturePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeaturePropertyType



namespace gie
{

namespace gml
{	

class CFeaturePropertyType : public TypeBase
{
public:
	gie_EXPORT CFeaturePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CFeaturePropertyType(CFeaturePropertyType const& init);
	void operator=(CFeaturePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFeaturePropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CFeaturePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CFeaturePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CDirectedObservationType, _altova_mi_gml_altova_CFeaturePropertyType_altova_DirectedObservation> DirectedObservation;
	struct DirectedObservation { typedef Iterator<gml::CDirectedObservationType> iterator; };
	MemberElement<gml::CDirectedObservationAtDistanceType, _altova_mi_gml_altova_CFeaturePropertyType_altova_DirectedObservationAtDistance> DirectedObservationAtDistance;
	struct DirectedObservationAtDistance { typedef Iterator<gml::CDirectedObservationAtDistanceType> iterator; };
	MemberElement<gml::CDynamicFeatureType, _altova_mi_gml_altova_CFeaturePropertyType_altova_DynamicFeature> DynamicFeature;
	struct DynamicFeature { typedef Iterator<gml::CDynamicFeatureType> iterator; };
	MemberElement<gml::CDynamicFeatureCollectionType, _altova_mi_gml_altova_CFeaturePropertyType_altova_DynamicFeatureCollection> DynamicFeatureCollection;
	struct DynamicFeatureCollection { typedef Iterator<gml::CDynamicFeatureCollectionType> iterator; };
	MemberElement<gml::CFeatureCollectionType, _altova_mi_gml_altova_CFeaturePropertyType_altova_FeatureCollection> FeatureCollection;
	struct FeatureCollection { typedef Iterator<gml::CFeatureCollectionType> iterator; };
	MemberElement<gml::CGridCoverageType, _altova_mi_gml_altova_CFeaturePropertyType_altova_GridCoverage> GridCoverage;
	struct GridCoverage { typedef Iterator<gml::CGridCoverageType> iterator; };
	MemberElement<gml::CMultiCurveCoverageType, _altova_mi_gml_altova_CFeaturePropertyType_altova_MultiCurveCoverage> MultiCurveCoverage;
	struct MultiCurveCoverage { typedef Iterator<gml::CMultiCurveCoverageType> iterator; };
	MemberElement<gml::CMultiPointCoverageType, _altova_mi_gml_altova_CFeaturePropertyType_altova_MultiPointCoverage> MultiPointCoverage;
	struct MultiPointCoverage { typedef Iterator<gml::CMultiPointCoverageType> iterator; };
	MemberElement<gml::CMultiSolidCoverageType, _altova_mi_gml_altova_CFeaturePropertyType_altova_MultiSolidCoverage> MultiSolidCoverage;
	struct MultiSolidCoverage { typedef Iterator<gml::CMultiSolidCoverageType> iterator; };
	MemberElement<gml::CMultiSurfaceCoverageType, _altova_mi_gml_altova_CFeaturePropertyType_altova_MultiSurfaceCoverage> MultiSurfaceCoverage;
	struct MultiSurfaceCoverage { typedef Iterator<gml::CMultiSurfaceCoverageType> iterator; };
	MemberElement<gml::CObservationType, _altova_mi_gml_altova_CFeaturePropertyType_altova_Observation> Observation;
	struct Observation { typedef Iterator<gml::CObservationType> iterator; };
	MemberElement<gml::CRectifiedGridCoverageType, _altova_mi_gml_altova_CFeaturePropertyType_altova_RectifiedGridCoverage> RectifiedGridCoverage;
	struct RectifiedGridCoverage { typedef Iterator<gml::CRectifiedGridCoverageType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeaturePropertyType
