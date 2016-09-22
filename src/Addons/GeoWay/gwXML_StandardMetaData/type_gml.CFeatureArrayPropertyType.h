#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeatureArrayPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeatureArrayPropertyType



namespace gie
{

namespace gml
{	

class CFeatureArrayPropertyType : public TypeBase
{
public:
	gie_EXPORT CFeatureArrayPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CFeatureArrayPropertyType(CFeatureArrayPropertyType const& init);
	void operator=(CFeatureArrayPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFeatureArrayPropertyType); }
	MemberElement<gml::CDirectedObservationType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_DirectedObservation> DirectedObservation;
	struct DirectedObservation { typedef Iterator<gml::CDirectedObservationType> iterator; };
	MemberElement<gml::CDirectedObservationAtDistanceType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_DirectedObservationAtDistance> DirectedObservationAtDistance;
	struct DirectedObservationAtDistance { typedef Iterator<gml::CDirectedObservationAtDistanceType> iterator; };
	MemberElement<gml::CDynamicFeatureType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_DynamicFeature> DynamicFeature;
	struct DynamicFeature { typedef Iterator<gml::CDynamicFeatureType> iterator; };
	MemberElement<gml::CDynamicFeatureCollectionType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_DynamicFeatureCollection> DynamicFeatureCollection;
	struct DynamicFeatureCollection { typedef Iterator<gml::CDynamicFeatureCollectionType> iterator; };
	MemberElement<gml::CFeatureCollectionType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_FeatureCollection> FeatureCollection;
	struct FeatureCollection { typedef Iterator<gml::CFeatureCollectionType> iterator; };
	MemberElement<gml::CGridCoverageType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_GridCoverage> GridCoverage;
	struct GridCoverage { typedef Iterator<gml::CGridCoverageType> iterator; };
	MemberElement<gml::CMultiCurveCoverageType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_MultiCurveCoverage> MultiCurveCoverage;
	struct MultiCurveCoverage { typedef Iterator<gml::CMultiCurveCoverageType> iterator; };
	MemberElement<gml::CMultiPointCoverageType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_MultiPointCoverage> MultiPointCoverage;
	struct MultiPointCoverage { typedef Iterator<gml::CMultiPointCoverageType> iterator; };
	MemberElement<gml::CMultiSolidCoverageType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_MultiSolidCoverage> MultiSolidCoverage;
	struct MultiSolidCoverage { typedef Iterator<gml::CMultiSolidCoverageType> iterator; };
	MemberElement<gml::CMultiSurfaceCoverageType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_MultiSurfaceCoverage> MultiSurfaceCoverage;
	struct MultiSurfaceCoverage { typedef Iterator<gml::CMultiSurfaceCoverageType> iterator; };
	MemberElement<gml::CObservationType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_Observation> Observation;
	struct Observation { typedef Iterator<gml::CObservationType> iterator; };
	MemberElement<gml::CRectifiedGridCoverageType, _altova_mi_gml_altova_CFeatureArrayPropertyType_altova_RectifiedGridCoverage> RectifiedGridCoverage;
	struct RectifiedGridCoverage { typedef Iterator<gml::CRectifiedGridCoverageType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeatureArrayPropertyType
