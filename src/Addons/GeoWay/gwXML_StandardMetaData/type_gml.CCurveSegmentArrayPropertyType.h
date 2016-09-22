#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCurveSegmentArrayPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCurveSegmentArrayPropertyType



namespace gie
{

namespace gml
{	

class CCurveSegmentArrayPropertyType : public TypeBase
{
public:
	gie_EXPORT CCurveSegmentArrayPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCurveSegmentArrayPropertyType(CCurveSegmentArrayPropertyType const& init);
	void operator=(CCurveSegmentArrayPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCurveSegmentArrayPropertyType); }
	MemberElement<gml::CArcType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_Arc> Arc;
	struct Arc { typedef Iterator<gml::CArcType> iterator; };
	MemberElement<gml::CArcByBulgeType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_ArcByBulge> ArcByBulge;
	struct ArcByBulge { typedef Iterator<gml::CArcByBulgeType> iterator; };
	MemberElement<gml::CArcByCenterPointType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_ArcByCenterPoint> ArcByCenterPoint;
	struct ArcByCenterPoint { typedef Iterator<gml::CArcByCenterPointType> iterator; };
	MemberElement<gml::CArcStringType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_ArcString> ArcString;
	struct ArcString { typedef Iterator<gml::CArcStringType> iterator; };
	MemberElement<gml::CArcStringByBulgeType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_ArcStringByBulge> ArcStringByBulge;
	struct ArcStringByBulge { typedef Iterator<gml::CArcStringByBulgeType> iterator; };
	MemberElement<gml::CBSplineType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_BSpline> BSpline;
	struct BSpline { typedef Iterator<gml::CBSplineType> iterator; };
	MemberElement<gml::CBezierType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_Bezier> Bezier;
	struct Bezier { typedef Iterator<gml::CBezierType> iterator; };
	MemberElement<gml::CCircleType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_Circle> Circle;
	struct Circle { typedef Iterator<gml::CCircleType> iterator; };
	MemberElement<gml::CCircleByCenterPointType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_CircleByCenterPoint> CircleByCenterPoint;
	struct CircleByCenterPoint { typedef Iterator<gml::CCircleByCenterPointType> iterator; };
	MemberElement<gml::CClothoidType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_Clothoid> Clothoid;
	struct Clothoid { typedef Iterator<gml::CClothoidType> iterator; };
	MemberElement<gml::CCubicSplineType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_CubicSpline> CubicSpline;
	struct CubicSpline { typedef Iterator<gml::CCubicSplineType> iterator; };
	MemberElement<gml::CGeodesicType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_Geodesic> Geodesic;
	struct Geodesic { typedef Iterator<gml::CGeodesicType> iterator; };
	MemberElement<gml::CGeodesicStringType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_GeodesicString> GeodesicString;
	struct GeodesicString { typedef Iterator<gml::CGeodesicStringType> iterator; };
	MemberElement<gml::CLineStringSegmentType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_LineStringSegment> LineStringSegment;
	struct LineStringSegment { typedef Iterator<gml::CLineStringSegmentType> iterator; };
	MemberElement<gml::COffsetCurveType, _altova_mi_gml_altova_CCurveSegmentArrayPropertyType_altova_OffsetCurve> OffsetCurve;
	struct OffsetCurve { typedef Iterator<gml::COffsetCurveType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCurveSegmentArrayPropertyType
