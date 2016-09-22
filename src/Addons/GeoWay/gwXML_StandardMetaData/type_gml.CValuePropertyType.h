#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CValuePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CValuePropertyType



namespace gie
{

namespace gml
{	

class CValuePropertyType : public TypeBase
{
public:
	gie_EXPORT CValuePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CValuePropertyType(CValuePropertyType const& init);
	void operator=(CValuePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CValuePropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CValuePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CValuePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gie2::CBooleanType, _altova_mi_gml_altova_CValuePropertyType_altova_Boolean> Boolean;
	struct Boolean { typedef Iterator<gie2::CBooleanType> iterator; };
	MemberElement<gml::CbooleanOrNilReasonListType, _altova_mi_gml_altova_CValuePropertyType_altova_BooleanList> BooleanList;
	struct BooleanList { typedef Iterator<gml::CbooleanOrNilReasonListType> iterator; };
	MemberElement<gie2::CCategoryType, _altova_mi_gml_altova_CValuePropertyType_altova_Category> Category;
	struct Category { typedef Iterator<gie2::CCategoryType> iterator; };
	MemberElement<gml::CCategoryExtentType, _altova_mi_gml_altova_CValuePropertyType_altova_CategoryExtent> CategoryExtent;
	struct CategoryExtent { typedef Iterator<gml::CCategoryExtentType> iterator; };
	MemberElement<gml::CCodeOrNilReasonListType, _altova_mi_gml_altova_CValuePropertyType_altova_CategoryList> CategoryList;
	struct CategoryList { typedef Iterator<gml::CCodeOrNilReasonListType> iterator; };
	MemberElement<gml::CCompositeValueType, _altova_mi_gml_altova_CValuePropertyType_altova_CompositeValue> CompositeValue;
	struct CompositeValue { typedef Iterator<gml::CCompositeValueType> iterator; };
	MemberElement<gie2::CCountType, _altova_mi_gml_altova_CValuePropertyType_altova_Count> Count;
	struct Count { typedef Iterator<gie2::CCountType> iterator; };
	MemberElement<gml::CCountExtentTypeType, _altova_mi_gml_altova_CValuePropertyType_altova_CountExtent> CountExtent;
	struct CountExtent { typedef Iterator<gml::CCountExtentTypeType> iterator; };
	MemberElement<gml::CintegerOrNilReasonListType, _altova_mi_gml_altova_CValuePropertyType_altova_CountList> CountList;
	struct CountList { typedef Iterator<gml::CintegerOrNilReasonListType> iterator; };
	MemberElement<gie2::CQuantityType, _altova_mi_gml_altova_CValuePropertyType_altova_Quantity> Quantity;
	struct Quantity { typedef Iterator<gie2::CQuantityType> iterator; };
	MemberElement<gml::CQuantityExtentType, _altova_mi_gml_altova_CValuePropertyType_altova_QuantityExtent> QuantityExtent;
	struct QuantityExtent { typedef Iterator<gml::CQuantityExtentType> iterator; };
	MemberElement<gml::CMeasureOrNilReasonListType, _altova_mi_gml_altova_CValuePropertyType_altova_QuantityList> QuantityList;
	struct QuantityList { typedef Iterator<gml::CMeasureOrNilReasonListType> iterator; };
	MemberElement<gml::CValueArrayType, _altova_mi_gml_altova_CValuePropertyType_altova_ValueArray> ValueArray;
	struct ValueArray { typedef Iterator<gml::CValueArrayType> iterator; };
	MemberElement<gml::CCompositeCurveType, _altova_mi_gml_altova_CValuePropertyType_altova_CompositeCurve> CompositeCurve;
	struct CompositeCurve { typedef Iterator<gml::CCompositeCurveType> iterator; };
	MemberElement<gml::CCompositeSolidType, _altova_mi_gml_altova_CValuePropertyType_altova_CompositeSolid> CompositeSolid;
	struct CompositeSolid { typedef Iterator<gml::CCompositeSolidType> iterator; };
	MemberElement<gml::CCompositeSurfaceType, _altova_mi_gml_altova_CValuePropertyType_altova_CompositeSurface> CompositeSurface;
	struct CompositeSurface { typedef Iterator<gml::CCompositeSurfaceType> iterator; };
	MemberElement<gml::CCurveType, _altova_mi_gml_altova_CValuePropertyType_altova_Curve> Curve;
	struct Curve { typedef Iterator<gml::CCurveType> iterator; };
	MemberElement<gml::CGeometricComplexType, _altova_mi_gml_altova_CValuePropertyType_altova_GeometricComplex> GeometricComplex;
	struct GeometricComplex { typedef Iterator<gml::CGeometricComplexType> iterator; };
	MemberElement<gml::CGridType, _altova_mi_gml_altova_CValuePropertyType_altova_Grid> Grid;
	struct Grid { typedef Iterator<gml::CGridType> iterator; };
	MemberElement<gml::CLineStringType, _altova_mi_gml_altova_CValuePropertyType_altova_LineString> LineString;
	struct LineString { typedef Iterator<gml::CLineStringType> iterator; };
	MemberElement<gml::CMultiCurveType, _altova_mi_gml_altova_CValuePropertyType_altova_MultiCurve> MultiCurve;
	struct MultiCurve { typedef Iterator<gml::CMultiCurveType> iterator; };
	MemberElement<gml::CMultiGeometryType, _altova_mi_gml_altova_CValuePropertyType_altova_MultiGeometry> MultiGeometry;
	struct MultiGeometry { typedef Iterator<gml::CMultiGeometryType> iterator; };
	MemberElement<gml::CMultiPointType, _altova_mi_gml_altova_CValuePropertyType_altova_MultiPoint> MultiPoint;
	struct MultiPoint { typedef Iterator<gml::CMultiPointType> iterator; };
	MemberElement<gml::CMultiSolidType, _altova_mi_gml_altova_CValuePropertyType_altova_MultiSolid> MultiSolid;
	struct MultiSolid { typedef Iterator<gml::CMultiSolidType> iterator; };
	MemberElement<gml::CMultiSurfaceType, _altova_mi_gml_altova_CValuePropertyType_altova_MultiSurface> MultiSurface;
	struct MultiSurface { typedef Iterator<gml::CMultiSurfaceType> iterator; };
	MemberElement<gml::COrientableCurveType, _altova_mi_gml_altova_CValuePropertyType_altova_OrientableCurve> OrientableCurve;
	struct OrientableCurve { typedef Iterator<gml::COrientableCurveType> iterator; };
	MemberElement<gml::COrientableSurfaceType, _altova_mi_gml_altova_CValuePropertyType_altova_OrientableSurface> OrientableSurface;
	struct OrientableSurface { typedef Iterator<gml::COrientableSurfaceType> iterator; };
	MemberElement<gml::CPointType, _altova_mi_gml_altova_CValuePropertyType_altova_Point> Point;
	struct Point { typedef Iterator<gml::CPointType> iterator; };
	MemberElement<gml::CPolygonType, _altova_mi_gml_altova_CValuePropertyType_altova_Polygon> Polygon;
	struct Polygon { typedef Iterator<gml::CPolygonType> iterator; };
	MemberElement<gml::CPolyhedralSurfaceType, _altova_mi_gml_altova_CValuePropertyType_altova_PolyhedralSurface> PolyhedralSurface;
	struct PolyhedralSurface { typedef Iterator<gml::CPolyhedralSurfaceType> iterator; };
	MemberElement<gml::CRectifiedGridType, _altova_mi_gml_altova_CValuePropertyType_altova_RectifiedGrid> RectifiedGrid;
	struct RectifiedGrid { typedef Iterator<gml::CRectifiedGridType> iterator; };
	MemberElement<gml::CSolidType, _altova_mi_gml_altova_CValuePropertyType_altova_Solid> Solid;
	struct Solid { typedef Iterator<gml::CSolidType> iterator; };
	MemberElement<gml::CSurfaceType, _altova_mi_gml_altova_CValuePropertyType_altova_Surface> Surface;
	struct Surface { typedef Iterator<gml::CSurfaceType> iterator; };
	MemberElement<gml::CTinType, _altova_mi_gml_altova_CValuePropertyType_altova_Tin> Tin;
	struct Tin { typedef Iterator<gml::CTinType> iterator; };
	MemberElement<gml::CTriangulatedSurfaceType, _altova_mi_gml_altova_CValuePropertyType_altova_TriangulatedSurface> TriangulatedSurface;
	struct TriangulatedSurface { typedef Iterator<gml::CTriangulatedSurfaceType> iterator; };
	MemberElement<gcv::CTM_GeometricPrimitive_Type, _altova_mi_gml_altova_CValuePropertyType_altova_TM_GeometricPrimitive> TM_GeometricPrimitive;
	struct TM_GeometricPrimitive { typedef Iterator<gcv::CTM_GeometricPrimitive_Type> iterator; };
	MemberElement<gcv::CTM_Period_Type, _altova_mi_gml_altova_CValuePropertyType_altova_TM_Period> TM_Period;
	struct TM_Period { typedef Iterator<gcv::CTM_Period_Type> iterator; };
	MemberElement<gml::CTimeEdgeType, _altova_mi_gml_altova_CValuePropertyType_altova_TimeEdge> TimeEdge;
	struct TimeEdge { typedef Iterator<gml::CTimeEdgeType> iterator; };
	MemberElement<gml::CTimeInstantType, _altova_mi_gml_altova_CValuePropertyType_altova_TimeInstant> TimeInstant;
	struct TimeInstant { typedef Iterator<gml::CTimeInstantType> iterator; };
	MemberElement<gml::CTimeNodeType, _altova_mi_gml_altova_CValuePropertyType_altova_TimeNode> TimeNode;
	struct TimeNode { typedef Iterator<gml::CTimeNodeType> iterator; };
	MemberElement<gml::CTimePeriodType, _altova_mi_gml_altova_CValuePropertyType_altova_TimePeriod> TimePeriod;
	struct TimePeriod { typedef Iterator<gml::CTimePeriodType> iterator; };
	MemberElement<gml::CTimeTopologyComplexType, _altova_mi_gml_altova_CValuePropertyType_altova_TimeTopologyComplex> TimeTopologyComplex;
	struct TimeTopologyComplex { typedef Iterator<gml::CTimeTopologyComplexType> iterator; };
	MemberElement<gml::CNilReasonTypeType, _altova_mi_gml_altova_CValuePropertyType_altova_Null> Null;
	struct Null { typedef Iterator<gml::CNilReasonTypeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CValuePropertyType
