#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAssociationRoleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAssociationRoleType



namespace gie
{

namespace gml
{	

class CAssociationRoleType : public TypeBase
{
public:
	gie_EXPORT CAssociationRoleType(xercesc::DOMNode* const& init);
	gie_EXPORT CAssociationRoleType(CAssociationRoleType const& init);
	void operator=(CAssociationRoleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAssociationRoleType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CAssociationRoleType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CAssociationRoleType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gcv::CTM_GeometricPrimitive_Type, _altova_mi_gml_altova_CAssociationRoleType_altova_TM_GeometricPrimitive> TM_GeometricPrimitive;
	struct TM_GeometricPrimitive { typedef Iterator<gcv::CTM_GeometricPrimitive_Type> iterator; };
	MemberElement<gcv::CTM_Period_Type, _altova_mi_gml_altova_CAssociationRoleType_altova_TM_Period> TM_Period;
	struct TM_Period { typedef Iterator<gcv::CTM_Period_Type> iterator; };
	MemberElement<gml::CAffineCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_AffineCS> AffineCS;
	struct AffineCS { typedef Iterator<gml::CAffineCSType> iterator; };
	MemberElement<gml::CAffinePlacementType, _altova_mi_gml_altova_CAssociationRoleType_altova_AffinePlacement> AffinePlacement;
	struct AffinePlacement { typedef Iterator<gml::CAffinePlacementType> iterator; };
	MemberElement<gml::CArcType, _altova_mi_gml_altova_CAssociationRoleType_altova_Arc> Arc;
	struct Arc { typedef Iterator<gml::CArcType> iterator; };
	MemberElement<gml::CArcByBulgeType, _altova_mi_gml_altova_CAssociationRoleType_altova_ArcByBulge> ArcByBulge;
	struct ArcByBulge { typedef Iterator<gml::CArcByBulgeType> iterator; };
	MemberElement<gml::CArcByCenterPointType, _altova_mi_gml_altova_CAssociationRoleType_altova_ArcByCenterPoint> ArcByCenterPoint;
	struct ArcByCenterPoint { typedef Iterator<gml::CArcByCenterPointType> iterator; };
	MemberElement<gml::CArcStringType, _altova_mi_gml_altova_CAssociationRoleType_altova_ArcString> ArcString;
	struct ArcString { typedef Iterator<gml::CArcStringType> iterator; };
	MemberElement<gml::CArcStringByBulgeType, _altova_mi_gml_altova_CAssociationRoleType_altova_ArcStringByBulge> ArcStringByBulge;
	struct ArcStringByBulge { typedef Iterator<gml::CArcStringByBulgeType> iterator; };
	MemberElement<gml::CArrayType, _altova_mi_gml_altova_CAssociationRoleType_altova_Array> Array;
	struct Array { typedef Iterator<gml::CArrayType> iterator; };
	MemberElement<gml::CBSplineType, _altova_mi_gml_altova_CAssociationRoleType_altova_BSpline> BSpline;
	struct BSpline { typedef Iterator<gml::CBSplineType> iterator; };
	MemberElement<gml::CBagType, _altova_mi_gml_altova_CAssociationRoleType_altova_Bag> Bag;
	struct Bag { typedef Iterator<gml::CBagType> iterator; };
	MemberElement<gml::CBaseUnitType, _altova_mi_gml_altova_CAssociationRoleType_altova_BaseUnit> BaseUnit;
	struct BaseUnit { typedef Iterator<gml::CBaseUnitType> iterator; };
	MemberElement<gml::CBezierType, _altova_mi_gml_altova_CAssociationRoleType_altova_Bezier> Bezier;
	struct Bezier { typedef Iterator<gml::CBezierType> iterator; };
	MemberElement<gie2::CBooleanType, _altova_mi_gml_altova_CAssociationRoleType_altova_Boolean> Boolean;
	struct Boolean { typedef Iterator<gie2::CBooleanType> iterator; };
	MemberElement<gml::CbooleanOrNilReasonListType, _altova_mi_gml_altova_CAssociationRoleType_altova_BooleanList> BooleanList;
	struct BooleanList { typedef Iterator<gml::CbooleanOrNilReasonListType> iterator; };
	MemberElement<gml::CCartesianCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_CartesianCS> CartesianCS;
	struct CartesianCS { typedef Iterator<gml::CCartesianCSType> iterator; };
	MemberElement<gie2::CCategoryType, _altova_mi_gml_altova_CAssociationRoleType_altova_Category> Category;
	struct Category { typedef Iterator<gie2::CCategoryType> iterator; };
	MemberElement<gml::CCategoryExtentType, _altova_mi_gml_altova_CAssociationRoleType_altova_CategoryExtent> CategoryExtent;
	struct CategoryExtent { typedef Iterator<gml::CCategoryExtentType> iterator; };
	MemberElement<gml::CCodeOrNilReasonListType, _altova_mi_gml_altova_CAssociationRoleType_altova_CategoryList> CategoryList;
	struct CategoryList { typedef Iterator<gml::CCodeOrNilReasonListType> iterator; };
	MemberElement<gml::CCircleType, _altova_mi_gml_altova_CAssociationRoleType_altova_Circle> Circle;
	struct Circle { typedef Iterator<gml::CCircleType> iterator; };
	MemberElement<gml::CCircleByCenterPointType, _altova_mi_gml_altova_CAssociationRoleType_altova_CircleByCenterPoint> CircleByCenterPoint;
	struct CircleByCenterPoint { typedef Iterator<gml::CCircleByCenterPointType> iterator; };
	MemberElement<gml::CClothoidType, _altova_mi_gml_altova_CAssociationRoleType_altova_Clothoid> Clothoid;
	struct Clothoid { typedef Iterator<gml::CClothoidType> iterator; };
	MemberElement<gml::CCompositeCurveType, _altova_mi_gml_altova_CAssociationRoleType_altova_CompositeCurve> CompositeCurve;
	struct CompositeCurve { typedef Iterator<gml::CCompositeCurveType> iterator; };
	MemberElement<gml::CCompositeSolidType, _altova_mi_gml_altova_CAssociationRoleType_altova_CompositeSolid> CompositeSolid;
	struct CompositeSolid { typedef Iterator<gml::CCompositeSolidType> iterator; };
	MemberElement<gml::CCompositeSurfaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_CompositeSurface> CompositeSurface;
	struct CompositeSurface { typedef Iterator<gml::CCompositeSurfaceType> iterator; };
	MemberElement<gml::CCompositeValueType, _altova_mi_gml_altova_CAssociationRoleType_altova_CompositeValue> CompositeValue;
	struct CompositeValue { typedef Iterator<gml::CCompositeValueType> iterator; };
	MemberElement<gml::CCompoundCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_CompoundCRS> CompoundCRS;
	struct CompoundCRS { typedef Iterator<gml::CCompoundCRSType> iterator; };
	MemberElement<gml::CConcatenatedOperationType, _altova_mi_gml_altova_CAssociationRoleType_altova_ConcatenatedOperation> ConcatenatedOperation;
	struct ConcatenatedOperation { typedef Iterator<gml::CConcatenatedOperationType> iterator; };
	MemberElement<gml::CConventionalUnitType, _altova_mi_gml_altova_CAssociationRoleType_altova_ConventionalUnit> ConventionalUnit;
	struct ConventionalUnit { typedef Iterator<gml::CConventionalUnitType> iterator; };
	MemberElement<gml::CConversionType, _altova_mi_gml_altova_CAssociationRoleType_altova_Conversion> Conversion;
	struct Conversion { typedef Iterator<gml::CConversionType> iterator; };
	MemberElement<gml::CCoordinateSystemAxisType, _altova_mi_gml_altova_CAssociationRoleType_altova_CoordinateSystemAxis> CoordinateSystemAxis;
	struct CoordinateSystemAxis { typedef Iterator<gml::CCoordinateSystemAxisType> iterator; };
	MemberElement<gie2::CCountType, _altova_mi_gml_altova_CAssociationRoleType_altova_Count> Count;
	struct Count { typedef Iterator<gie2::CCountType> iterator; };
	MemberElement<gml::CCountExtentTypeType, _altova_mi_gml_altova_CAssociationRoleType_altova_CountExtent> CountExtent;
	struct CountExtent { typedef Iterator<gml::CCountExtentTypeType> iterator; };
	MemberElement<gml::CintegerOrNilReasonListType, _altova_mi_gml_altova_CAssociationRoleType_altova_CountList> CountList;
	struct CountList { typedef Iterator<gml::CintegerOrNilReasonListType> iterator; };
	MemberElement<gml::CMappingRuleType, _altova_mi_gml_altova_CAssociationRoleType_altova_CoverageMappingRule> CoverageMappingRule;
	struct CoverageMappingRule { typedef Iterator<gml::CMappingRuleType> iterator; };
	MemberElement<gml::CCubicSplineType, _altova_mi_gml_altova_CAssociationRoleType_altova_CubicSpline> CubicSpline;
	struct CubicSpline { typedef Iterator<gml::CCubicSplineType> iterator; };
	MemberElement<gml::CCurveType, _altova_mi_gml_altova_CAssociationRoleType_altova_Curve> Curve;
	struct Curve { typedef Iterator<gml::CCurveType> iterator; };
	MemberElement<gml::CCylindricalCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_CylindricalCS> CylindricalCS;
	struct CylindricalCS { typedef Iterator<gml::CCylindricalCSType> iterator; };
	MemberElement<gml::CDataBlockType, _altova_mi_gml_altova_CAssociationRoleType_altova_DataBlock> DataBlock;
	struct DataBlock { typedef Iterator<gml::CDataBlockType> iterator; };
	MemberElement<gml::CDefinitionType, _altova_mi_gml_altova_CAssociationRoleType_altova_Definition> Definition;
	struct Definition { typedef Iterator<gml::CDefinitionType> iterator; };
	MemberElement<gml::CDictionaryType, _altova_mi_gml_altova_CAssociationRoleType_altova_DefinitionCollection> DefinitionCollection;
	struct DefinitionCollection { typedef Iterator<gml::CDictionaryType> iterator; };
	MemberElement<gml::CDefinitionProxyType, _altova_mi_gml_altova_CAssociationRoleType_altova_DefinitionProxy> DefinitionProxy;
	struct DefinitionProxy { typedef Iterator<gml::CDefinitionProxyType> iterator; };
	MemberElement<gml::CDerivedCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_DerivedCRS> DerivedCRS;
	struct DerivedCRS { typedef Iterator<gml::CDerivedCRSType> iterator; };
	MemberElement<gml::CDerivedUnitType, _altova_mi_gml_altova_CAssociationRoleType_altova_DerivedUnit> DerivedUnit;
	struct DerivedUnit { typedef Iterator<gml::CDerivedUnitType> iterator; };
	MemberElement<gml::CDictionaryType, _altova_mi_gml_altova_CAssociationRoleType_altova_Dictionary> Dictionary;
	struct Dictionary { typedef Iterator<gml::CDictionaryType> iterator; };
	MemberElement<gml::CDirectedObservationType, _altova_mi_gml_altova_CAssociationRoleType_altova_DirectedObservation> DirectedObservation;
	struct DirectedObservation { typedef Iterator<gml::CDirectedObservationType> iterator; };
	MemberElement<gml::CDirectedObservationAtDistanceType, _altova_mi_gml_altova_CAssociationRoleType_altova_DirectedObservationAtDistance> DirectedObservationAtDistance;
	struct DirectedObservationAtDistance { typedef Iterator<gml::CDirectedObservationAtDistanceType> iterator; };
	MemberElement<gml::CDynamicFeatureType, _altova_mi_gml_altova_CAssociationRoleType_altova_DynamicFeature> DynamicFeature;
	struct DynamicFeature { typedef Iterator<gml::CDynamicFeatureType> iterator; };
	MemberElement<gml::CDynamicFeatureCollectionType, _altova_mi_gml_altova_CAssociationRoleType_altova_DynamicFeatureCollection> DynamicFeatureCollection;
	struct DynamicFeatureCollection { typedef Iterator<gml::CDynamicFeatureCollectionType> iterator; };
	MemberElement<gml::CEdgeType, _altova_mi_gml_altova_CAssociationRoleType_altova_Edge> Edge;
	struct Edge { typedef Iterator<gml::CEdgeType> iterator; };
	MemberElement<gml::CEllipsoidType, _altova_mi_gml_altova_CAssociationRoleType_altova_Ellipsoid> Ellipsoid;
	struct Ellipsoid { typedef Iterator<gml::CEllipsoidType> iterator; };
	MemberElement<gml::CEllipsoidalCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_EllipsoidalCS> EllipsoidalCS;
	struct EllipsoidalCS { typedef Iterator<gml::CEllipsoidalCSType> iterator; };
	MemberElement<gml::CEngineeringCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_EngineeringCRS> EngineeringCRS;
	struct EngineeringCRS { typedef Iterator<gml::CEngineeringCRSType> iterator; };
	MemberElement<gml::CEngineeringDatumType, _altova_mi_gml_altova_CAssociationRoleType_altova_EngineeringDatum> EngineeringDatum;
	struct EngineeringDatum { typedef Iterator<gml::CEngineeringDatumType> iterator; };
	MemberElement<gml::CEnvelopeType, _altova_mi_gml_altova_CAssociationRoleType_altova_Envelope> Envelope;
	struct Envelope { typedef Iterator<gml::CEnvelopeType> iterator; };
	MemberElement<gml::CEnvelopeWithTimePeriodType, _altova_mi_gml_altova_CAssociationRoleType_altova_EnvelopeWithTimePeriod> EnvelopeWithTimePeriod;
	struct EnvelopeWithTimePeriod { typedef Iterator<gml::CEnvelopeWithTimePeriodType> iterator; };
	MemberElement<gml::CFaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_Face> Face;
	struct Face { typedef Iterator<gml::CFaceType> iterator; };
	MemberElement<gml::CFeatureCollectionType, _altova_mi_gml_altova_CAssociationRoleType_altova_FeatureCollection> FeatureCollection;
	struct FeatureCollection { typedef Iterator<gml::CFeatureCollectionType> iterator; };
	MemberElement<gml::CFileType, _altova_mi_gml_altova_CAssociationRoleType_altova_File> File;
	struct File { typedef Iterator<gml::CFileType> iterator; };
	MemberElement<gml::CGenericMetaDataType, _altova_mi_gml_altova_CAssociationRoleType_altova_GenericMetaData> GenericMetaData;
	struct GenericMetaData { typedef Iterator<gml::CGenericMetaDataType> iterator; };
	MemberElement<gml::CGeocentricCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_GeocentricCRS> GeocentricCRS;
	struct GeocentricCRS { typedef Iterator<gml::CGeocentricCRSType> iterator; };
	MemberElement<gml::CGeodesicType, _altova_mi_gml_altova_CAssociationRoleType_altova_Geodesic> Geodesic;
	struct Geodesic { typedef Iterator<gml::CGeodesicType> iterator; };
	MemberElement<gml::CGeodesicStringType, _altova_mi_gml_altova_CAssociationRoleType_altova_GeodesicString> GeodesicString;
	struct GeodesicString { typedef Iterator<gml::CGeodesicStringType> iterator; };
	MemberElement<gml::CGeodeticCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_GeodeticCRS> GeodeticCRS;
	struct GeodeticCRS { typedef Iterator<gml::CGeodeticCRSType> iterator; };
	MemberElement<gml::CGeodeticDatumType, _altova_mi_gml_altova_CAssociationRoleType_altova_GeodeticDatum> GeodeticDatum;
	struct GeodeticDatum { typedef Iterator<gml::CGeodeticDatumType> iterator; };
	MemberElement<gml::CGeographicCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_GeographicCRS> GeographicCRS;
	struct GeographicCRS { typedef Iterator<gml::CGeographicCRSType> iterator; };
	MemberElement<gml::CGeometricComplexType, _altova_mi_gml_altova_CAssociationRoleType_altova_GeometricComplex> GeometricComplex;
	struct GeometricComplex { typedef Iterator<gml::CGeometricComplexType> iterator; };
	MemberElement<gml::CGridType, _altova_mi_gml_altova_CAssociationRoleType_altova_Grid> Grid;
	struct Grid { typedef Iterator<gml::CGridType> iterator; };
	MemberElement<gml::CGridCoverageType, _altova_mi_gml_altova_CAssociationRoleType_altova_GridCoverage> GridCoverage;
	struct GridCoverage { typedef Iterator<gml::CGridCoverageType> iterator; };
	MemberElement<gml::CGridFunctionType, _altova_mi_gml_altova_CAssociationRoleType_altova_GridFunction> GridFunction;
	struct GridFunction { typedef Iterator<gml::CGridFunctionType> iterator; };
	MemberElement<gml::CImageCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_ImageCRS> ImageCRS;
	struct ImageCRS { typedef Iterator<gml::CImageCRSType> iterator; };
	MemberElement<gml::CImageDatumType, _altova_mi_gml_altova_CAssociationRoleType_altova_ImageDatum> ImageDatum;
	struct ImageDatum { typedef Iterator<gml::CImageDatumType> iterator; };
	MemberElement<gml::CLineStringType, _altova_mi_gml_altova_CAssociationRoleType_altova_LineString> LineString;
	struct LineString { typedef Iterator<gml::CLineStringType> iterator; };
	MemberElement<gml::CLineStringSegmentType, _altova_mi_gml_altova_CAssociationRoleType_altova_LineStringSegment> LineStringSegment;
	struct LineStringSegment { typedef Iterator<gml::CLineStringSegmentType> iterator; };
	MemberElement<gml::CLinearCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_LinearCS> LinearCS;
	struct LinearCS { typedef Iterator<gml::CLinearCSType> iterator; };
	MemberElement<gml::CLinearRingType, _altova_mi_gml_altova_CAssociationRoleType_altova_LinearRing> LinearRing;
	struct LinearRing { typedef Iterator<gml::CLinearRingType> iterator; };
	MemberElement<gml::CMovingObjectStatusType, _altova_mi_gml_altova_CAssociationRoleType_altova_MovingObjectStatus> MovingObjectStatus;
	struct MovingObjectStatus { typedef Iterator<gml::CMovingObjectStatusType> iterator; };
	MemberElement<gml::CMultiCurveType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiCurve> MultiCurve;
	struct MultiCurve { typedef Iterator<gml::CMultiCurveType> iterator; };
	MemberElement<gml::CMultiCurveCoverageType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiCurveCoverage> MultiCurveCoverage;
	struct MultiCurveCoverage { typedef Iterator<gml::CMultiCurveCoverageType> iterator; };
	MemberElement<gml::CMultiGeometryType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiGeometry> MultiGeometry;
	struct MultiGeometry { typedef Iterator<gml::CMultiGeometryType> iterator; };
	MemberElement<gml::CMultiPointType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiPoint> MultiPoint;
	struct MultiPoint { typedef Iterator<gml::CMultiPointType> iterator; };
	MemberElement<gml::CMultiPointCoverageType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiPointCoverage> MultiPointCoverage;
	struct MultiPointCoverage { typedef Iterator<gml::CMultiPointCoverageType> iterator; };
	MemberElement<gml::CMultiSolidType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiSolid> MultiSolid;
	struct MultiSolid { typedef Iterator<gml::CMultiSolidType> iterator; };
	MemberElement<gml::CMultiSolidCoverageType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiSolidCoverage> MultiSolidCoverage;
	struct MultiSolidCoverage { typedef Iterator<gml::CMultiSolidCoverageType> iterator; };
	MemberElement<gml::CMultiSurfaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiSurface> MultiSurface;
	struct MultiSurface { typedef Iterator<gml::CMultiSurfaceType> iterator; };
	MemberElement<gml::CMultiSurfaceCoverageType, _altova_mi_gml_altova_CAssociationRoleType_altova_MultiSurfaceCoverage> MultiSurfaceCoverage;
	struct MultiSurfaceCoverage { typedef Iterator<gml::CMultiSurfaceCoverageType> iterator; };
	MemberElement<gml::CNodeType, _altova_mi_gml_altova_CAssociationRoleType_altova_Node> Node;
	struct Node { typedef Iterator<gml::CNodeType> iterator; };
	MemberElement<gml::CObliqueCartesianCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_ObliqueCartesianCS> ObliqueCartesianCS;
	struct ObliqueCartesianCS { typedef Iterator<gml::CObliqueCartesianCSType> iterator; };
	MemberElement<gml::CObservationType, _altova_mi_gml_altova_CAssociationRoleType_altova_Observation> Observation;
	struct Observation { typedef Iterator<gml::CObservationType> iterator; };
	MemberElement<gml::COffsetCurveType, _altova_mi_gml_altova_CAssociationRoleType_altova_OffsetCurve> OffsetCurve;
	struct OffsetCurve { typedef Iterator<gml::COffsetCurveType> iterator; };
	MemberElement<gml::COperationMethodType, _altova_mi_gml_altova_CAssociationRoleType_altova_OperationMethod> OperationMethod;
	struct OperationMethod { typedef Iterator<gml::COperationMethodType> iterator; };
	MemberElement<gml::COperationParameterType, _altova_mi_gml_altova_CAssociationRoleType_altova_OperationParameter> OperationParameter;
	struct OperationParameter { typedef Iterator<gml::COperationParameterType> iterator; };
	MemberElement<gml::COperationParameterGroupType, _altova_mi_gml_altova_CAssociationRoleType_altova_OperationParameterGroup> OperationParameterGroup;
	struct OperationParameterGroup { typedef Iterator<gml::COperationParameterGroupType> iterator; };
	MemberElement<gml::COrientableCurveType, _altova_mi_gml_altova_CAssociationRoleType_altova_OrientableCurve> OrientableCurve;
	struct OrientableCurve { typedef Iterator<gml::COrientableCurveType> iterator; };
	MemberElement<gml::COrientableSurfaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_OrientableSurface> OrientableSurface;
	struct OrientableSurface { typedef Iterator<gml::COrientableSurfaceType> iterator; };
	MemberElement<gml::CParameterValueType, _altova_mi_gml_altova_CAssociationRoleType_altova_ParameterValue> ParameterValue;
	struct ParameterValue { typedef Iterator<gml::CParameterValueType> iterator; };
	MemberElement<gml::CParameterValueGroupType, _altova_mi_gml_altova_CAssociationRoleType_altova_ParameterValueGroup> ParameterValueGroup;
	struct ParameterValueGroup { typedef Iterator<gml::CParameterValueGroupType> iterator; };
	MemberElement<gml::CPassThroughOperationType, _altova_mi_gml_altova_CAssociationRoleType_altova_PassThroughOperation> PassThroughOperation;
	struct PassThroughOperation { typedef Iterator<gml::CPassThroughOperationType> iterator; };
	MemberElement<gml::CPointType, _altova_mi_gml_altova_CAssociationRoleType_altova_Point> Point;
	struct Point { typedef Iterator<gml::CPointType> iterator; };
	MemberElement<gml::CPolarCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_PolarCS> PolarCS;
	struct PolarCS { typedef Iterator<gml::CPolarCSType> iterator; };
	MemberElement<gml::CPolygonType, _altova_mi_gml_altova_CAssociationRoleType_altova_Polygon> Polygon;
	struct Polygon { typedef Iterator<gml::CPolygonType> iterator; };
	MemberElement<gml::CPolyhedralSurfaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_PolyhedralSurface> PolyhedralSurface;
	struct PolyhedralSurface { typedef Iterator<gml::CPolyhedralSurfaceType> iterator; };
	MemberElement<gml::CPrimeMeridianType, _altova_mi_gml_altova_CAssociationRoleType_altova_PrimeMeridian> PrimeMeridian;
	struct PrimeMeridian { typedef Iterator<gml::CPrimeMeridianType> iterator; };
	MemberElement<gml::CProjectedCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_ProjectedCRS> ProjectedCRS;
	struct ProjectedCRS { typedef Iterator<gml::CProjectedCRSType> iterator; };
	MemberElement<gie2::CQuantityType, _altova_mi_gml_altova_CAssociationRoleType_altova_Quantity> Quantity;
	struct Quantity { typedef Iterator<gie2::CQuantityType> iterator; };
	MemberElement<gml::CQuantityExtentType, _altova_mi_gml_altova_CAssociationRoleType_altova_QuantityExtent> QuantityExtent;
	struct QuantityExtent { typedef Iterator<gml::CQuantityExtentType> iterator; };
	MemberElement<gml::CMeasureOrNilReasonListType, _altova_mi_gml_altova_CAssociationRoleType_altova_QuantityList> QuantityList;
	struct QuantityList { typedef Iterator<gml::CMeasureOrNilReasonListType> iterator; };
	MemberElement<gml::CRectifiedGridType, _altova_mi_gml_altova_CAssociationRoleType_altova_RectifiedGrid> RectifiedGrid;
	struct RectifiedGrid { typedef Iterator<gml::CRectifiedGridType> iterator; };
	MemberElement<gml::CRectifiedGridCoverageType, _altova_mi_gml_altova_CAssociationRoleType_altova_RectifiedGridCoverage> RectifiedGridCoverage;
	struct RectifiedGridCoverage { typedef Iterator<gml::CRectifiedGridCoverageType> iterator; };
	MemberElement<gml::CRingType, _altova_mi_gml_altova_CAssociationRoleType_altova_Ring> Ring;
	struct Ring { typedef Iterator<gml::CRingType> iterator; };
	MemberElement<gml::CShellType, _altova_mi_gml_altova_CAssociationRoleType_altova_Shell> Shell;
	struct Shell { typedef Iterator<gml::CShellType> iterator; };
	MemberElement<gml::CSolidType, _altova_mi_gml_altova_CAssociationRoleType_altova_Solid> Solid;
	struct Solid { typedef Iterator<gml::CSolidType> iterator; };
	MemberElement<gml::CSphericalCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_SphericalCS> SphericalCS;
	struct SphericalCS { typedef Iterator<gml::CSphericalCSType> iterator; };
	MemberElement<gml::CSurfaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_Surface> Surface;
	struct Surface { typedef Iterator<gml::CSurfaceType> iterator; };
	MemberElement<gml::CTemporalCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_TemporalCRS> TemporalCRS;
	struct TemporalCRS { typedef Iterator<gml::CTemporalCRSType> iterator; };
	MemberElement<gml::CTemporalCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_TemporalCS> TemporalCS;
	struct TemporalCS { typedef Iterator<gml::CTemporalCSType> iterator; };
	MemberElement<gml::CTemporalDatumType, _altova_mi_gml_altova_CAssociationRoleType_altova_TemporalDatum> TemporalDatum;
	struct TemporalDatum { typedef Iterator<gml::CTemporalDatumType> iterator; };
	MemberElement<gml::CTimeCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeCS> TimeCS;
	struct TimeCS { typedef Iterator<gml::CTimeCSType> iterator; };
	MemberElement<gml::CTimeCalendarType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeCalendar> TimeCalendar;
	struct TimeCalendar { typedef Iterator<gml::CTimeCalendarType> iterator; };
	MemberElement<gml::CTimeClockType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeClock> TimeClock;
	struct TimeClock { typedef Iterator<gml::CTimeClockType> iterator; };
	MemberElement<gml::CTimeCoordinateSystemType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeCoordinateSystem> TimeCoordinateSystem;
	struct TimeCoordinateSystem { typedef Iterator<gml::CTimeCoordinateSystemType> iterator; };
	MemberElement<gml::CTimeEdgeType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeEdge> TimeEdge;
	struct TimeEdge { typedef Iterator<gml::CTimeEdgeType> iterator; };
	MemberElement<gml::CTimeInstantType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeInstant> TimeInstant;
	struct TimeInstant { typedef Iterator<gml::CTimeInstantType> iterator; };
	MemberElement<gml::CTimeNodeType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeNode> TimeNode;
	struct TimeNode { typedef Iterator<gml::CTimeNodeType> iterator; };
	MemberElement<gml::CTimeOrdinalReferenceSystemType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeOrdinalReferenceSystem> TimeOrdinalReferenceSystem;
	struct TimeOrdinalReferenceSystem { typedef Iterator<gml::CTimeOrdinalReferenceSystemType> iterator; };
	MemberElement<gml::CTimePeriodType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimePeriod> TimePeriod;
	struct TimePeriod { typedef Iterator<gml::CTimePeriodType> iterator; };
	MemberElement<gml::CTimeReferenceSystemType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeReferenceSystem> TimeReferenceSystem;
	struct TimeReferenceSystem { typedef Iterator<gml::CTimeReferenceSystemType> iterator; };
	MemberElement<gml::CTimeTopologyComplexType, _altova_mi_gml_altova_CAssociationRoleType_altova_TimeTopologyComplex> TimeTopologyComplex;
	struct TimeTopologyComplex { typedef Iterator<gml::CTimeTopologyComplexType> iterator; };
	MemberElement<gml::CTinType, _altova_mi_gml_altova_CAssociationRoleType_altova_Tin> Tin;
	struct Tin { typedef Iterator<gml::CTinType> iterator; };
	MemberElement<gml::CTopoComplexType, _altova_mi_gml_altova_CAssociationRoleType_altova_TopoComplex> TopoComplex;
	struct TopoComplex { typedef Iterator<gml::CTopoComplexType> iterator; };
	MemberElement<gml::CTopoSolidType, _altova_mi_gml_altova_CAssociationRoleType_altova_TopoSolid> TopoSolid;
	struct TopoSolid { typedef Iterator<gml::CTopoSolidType> iterator; };
	MemberElement<gml::CTransformationType, _altova_mi_gml_altova_CAssociationRoleType_altova_Transformation> Transformation;
	struct Transformation { typedef Iterator<gml::CTransformationType> iterator; };
	MemberElement<gml::CTriangulatedSurfaceType, _altova_mi_gml_altova_CAssociationRoleType_altova_TriangulatedSurface> TriangulatedSurface;
	struct TriangulatedSurface { typedef Iterator<gml::CTriangulatedSurfaceType> iterator; };
	MemberElement<gml::CUnitDefinitionType, _altova_mi_gml_altova_CAssociationRoleType_altova_UnitDefinition> UnitDefinition;
	struct UnitDefinition { typedef Iterator<gml::CUnitDefinitionType> iterator; };
	MemberElement<gml::CUserDefinedCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_UserDefinedCS> UserDefinedCS;
	struct UserDefinedCS { typedef Iterator<gml::CUserDefinedCSType> iterator; };
	MemberElement<gml::CValueArrayType, _altova_mi_gml_altova_CAssociationRoleType_altova_ValueArray> ValueArray;
	struct ValueArray { typedef Iterator<gml::CValueArrayType> iterator; };
	MemberElement<gml::CVerticalCRSType, _altova_mi_gml_altova_CAssociationRoleType_altova_VerticalCRS> VerticalCRS;
	struct VerticalCRS { typedef Iterator<gml::CVerticalCRSType> iterator; };
	MemberElement<gml::CVerticalCSType, _altova_mi_gml_altova_CAssociationRoleType_altova_VerticalCS> VerticalCS;
	struct VerticalCS { typedef Iterator<gml::CVerticalCSType> iterator; };
	MemberElement<gml::CVerticalDatumType, _altova_mi_gml_altova_CAssociationRoleType_altova_VerticalDatum> VerticalDatum;
	struct VerticalDatum { typedef Iterator<gml::CVerticalDatumType> iterator; };
	MemberElement<gml::CCoverageFunctionType, _altova_mi_gml_altova_CAssociationRoleType_altova_coverageFunction> coverageFunction;
	struct coverageFunction { typedef Iterator<gml::CCoverageFunctionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAssociationRoleType