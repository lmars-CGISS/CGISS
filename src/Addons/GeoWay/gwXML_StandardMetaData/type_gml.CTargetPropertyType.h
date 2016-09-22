#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTargetPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTargetPropertyType



namespace gie
{

namespace gml
{	

class CTargetPropertyType : public TypeBase
{
public:
	gie_EXPORT CTargetPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTargetPropertyType(CTargetPropertyType const& init);
	void operator=(CTargetPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTargetPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CTargetPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CTargetPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CDirectedObservationType, _altova_mi_gml_altova_CTargetPropertyType_altova_DirectedObservation> DirectedObservation;
	struct DirectedObservation { typedef Iterator<gml::CDirectedObservationType> iterator; };
	MemberElement<gml::CDirectedObservationAtDistanceType, _altova_mi_gml_altova_CTargetPropertyType_altova_DirectedObservationAtDistance> DirectedObservationAtDistance;
	struct DirectedObservationAtDistance { typedef Iterator<gml::CDirectedObservationAtDistanceType> iterator; };
	MemberElement<gml::CDynamicFeatureType, _altova_mi_gml_altova_CTargetPropertyType_altova_DynamicFeature> DynamicFeature;
	struct DynamicFeature { typedef Iterator<gml::CDynamicFeatureType> iterator; };
	MemberElement<gml::CDynamicFeatureCollectionType, _altova_mi_gml_altova_CTargetPropertyType_altova_DynamicFeatureCollection> DynamicFeatureCollection;
	struct DynamicFeatureCollection { typedef Iterator<gml::CDynamicFeatureCollectionType> iterator; };
	MemberElement<gml::CFeatureCollectionType, _altova_mi_gml_altova_CTargetPropertyType_altova_FeatureCollection> FeatureCollection;
	struct FeatureCollection { typedef Iterator<gml::CFeatureCollectionType> iterator; };
	MemberElement<gml::CGridCoverageType, _altova_mi_gml_altova_CTargetPropertyType_altova_GridCoverage> GridCoverage;
	struct GridCoverage { typedef Iterator<gml::CGridCoverageType> iterator; };
	MemberElement<gml::CMultiCurveCoverageType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiCurveCoverage> MultiCurveCoverage;
	struct MultiCurveCoverage { typedef Iterator<gml::CMultiCurveCoverageType> iterator; };
	MemberElement<gml::CMultiPointCoverageType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiPointCoverage> MultiPointCoverage;
	struct MultiPointCoverage { typedef Iterator<gml::CMultiPointCoverageType> iterator; };
	MemberElement<gml::CMultiSolidCoverageType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiSolidCoverage> MultiSolidCoverage;
	struct MultiSolidCoverage { typedef Iterator<gml::CMultiSolidCoverageType> iterator; };
	MemberElement<gml::CMultiSurfaceCoverageType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiSurfaceCoverage> MultiSurfaceCoverage;
	struct MultiSurfaceCoverage { typedef Iterator<gml::CMultiSurfaceCoverageType> iterator; };
	MemberElement<gml::CObservationType, _altova_mi_gml_altova_CTargetPropertyType_altova_Observation> Observation;
	struct Observation { typedef Iterator<gml::CObservationType> iterator; };
	MemberElement<gml::CRectifiedGridCoverageType, _altova_mi_gml_altova_CTargetPropertyType_altova_RectifiedGridCoverage> RectifiedGridCoverage;
	struct RectifiedGridCoverage { typedef Iterator<gml::CRectifiedGridCoverageType> iterator; };
	MemberElement<gml::CCompositeCurveType, _altova_mi_gml_altova_CTargetPropertyType_altova_CompositeCurve> CompositeCurve;
	struct CompositeCurve { typedef Iterator<gml::CCompositeCurveType> iterator; };
	MemberElement<gml::CCompositeSolidType, _altova_mi_gml_altova_CTargetPropertyType_altova_CompositeSolid> CompositeSolid;
	struct CompositeSolid { typedef Iterator<gml::CCompositeSolidType> iterator; };
	MemberElement<gml::CCompositeSurfaceType, _altova_mi_gml_altova_CTargetPropertyType_altova_CompositeSurface> CompositeSurface;
	struct CompositeSurface { typedef Iterator<gml::CCompositeSurfaceType> iterator; };
	MemberElement<gml::CCurveType, _altova_mi_gml_altova_CTargetPropertyType_altova_Curve> Curve;
	struct Curve { typedef Iterator<gml::CCurveType> iterator; };
	MemberElement<gml::CGeometricComplexType, _altova_mi_gml_altova_CTargetPropertyType_altova_GeometricComplex> GeometricComplex;
	struct GeometricComplex { typedef Iterator<gml::CGeometricComplexType> iterator; };
	MemberElement<gml::CGridType, _altova_mi_gml_altova_CTargetPropertyType_altova_Grid> Grid;
	struct Grid { typedef Iterator<gml::CGridType> iterator; };
	MemberElement<gml::CLineStringType, _altova_mi_gml_altova_CTargetPropertyType_altova_LineString> LineString;
	struct LineString { typedef Iterator<gml::CLineStringType> iterator; };
	MemberElement<gml::CMultiCurveType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiCurve> MultiCurve;
	struct MultiCurve { typedef Iterator<gml::CMultiCurveType> iterator; };
	MemberElement<gml::CMultiGeometryType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiGeometry> MultiGeometry;
	struct MultiGeometry { typedef Iterator<gml::CMultiGeometryType> iterator; };
	MemberElement<gml::CMultiPointType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiPoint> MultiPoint;
	struct MultiPoint { typedef Iterator<gml::CMultiPointType> iterator; };
	MemberElement<gml::CMultiSolidType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiSolid> MultiSolid;
	struct MultiSolid { typedef Iterator<gml::CMultiSolidType> iterator; };
	MemberElement<gml::CMultiSurfaceType, _altova_mi_gml_altova_CTargetPropertyType_altova_MultiSurface> MultiSurface;
	struct MultiSurface { typedef Iterator<gml::CMultiSurfaceType> iterator; };
	MemberElement<gml::COrientableCurveType, _altova_mi_gml_altova_CTargetPropertyType_altova_OrientableCurve> OrientableCurve;
	struct OrientableCurve { typedef Iterator<gml::COrientableCurveType> iterator; };
	MemberElement<gml::COrientableSurfaceType, _altova_mi_gml_altova_CTargetPropertyType_altova_OrientableSurface> OrientableSurface;
	struct OrientableSurface { typedef Iterator<gml::COrientableSurfaceType> iterator; };
	MemberElement<gml::CPointType, _altova_mi_gml_altova_CTargetPropertyType_altova_Point> Point;
	struct Point { typedef Iterator<gml::CPointType> iterator; };
	MemberElement<gml::CPolygonType, _altova_mi_gml_altova_CTargetPropertyType_altova_Polygon> Polygon;
	struct Polygon { typedef Iterator<gml::CPolygonType> iterator; };
	MemberElement<gml::CPolyhedralSurfaceType, _altova_mi_gml_altova_CTargetPropertyType_altova_PolyhedralSurface> PolyhedralSurface;
	struct PolyhedralSurface { typedef Iterator<gml::CPolyhedralSurfaceType> iterator; };
	MemberElement<gml::CRectifiedGridType, _altova_mi_gml_altova_CTargetPropertyType_altova_RectifiedGrid> RectifiedGrid;
	struct RectifiedGrid { typedef Iterator<gml::CRectifiedGridType> iterator; };
	MemberElement<gml::CSolidType, _altova_mi_gml_altova_CTargetPropertyType_altova_Solid> Solid;
	struct Solid { typedef Iterator<gml::CSolidType> iterator; };
	MemberElement<gml::CSurfaceType, _altova_mi_gml_altova_CTargetPropertyType_altova_Surface> Surface;
	struct Surface { typedef Iterator<gml::CSurfaceType> iterator; };
	MemberElement<gml::CTinType, _altova_mi_gml_altova_CTargetPropertyType_altova_Tin> Tin;
	struct Tin { typedef Iterator<gml::CTinType> iterator; };
	MemberElement<gml::CTriangulatedSurfaceType, _altova_mi_gml_altova_CTargetPropertyType_altova_TriangulatedSurface> TriangulatedSurface;
	struct TriangulatedSurface { typedef Iterator<gml::CTriangulatedSurfaceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTargetPropertyType
