#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricPrimitivePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricPrimitivePropertyType



namespace gie
{

namespace gml
{	

class CGeometricPrimitivePropertyType : public TypeBase
{
public:
	gie_EXPORT CGeometricPrimitivePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeometricPrimitivePropertyType(CGeometricPrimitivePropertyType const& init);
	void operator=(CGeometricPrimitivePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeometricPrimitivePropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CCompositeCurveType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_CompositeCurve> CompositeCurve;
	struct CompositeCurve { typedef Iterator<gml::CCompositeCurveType> iterator; };
	MemberElement<gml::CCompositeSolidType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_CompositeSolid> CompositeSolid;
	struct CompositeSolid { typedef Iterator<gml::CCompositeSolidType> iterator; };
	MemberElement<gml::CCompositeSurfaceType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_CompositeSurface> CompositeSurface;
	struct CompositeSurface { typedef Iterator<gml::CCompositeSurfaceType> iterator; };
	MemberElement<gml::CCurveType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_Curve> Curve;
	struct Curve { typedef Iterator<gml::CCurveType> iterator; };
	MemberElement<gml::CLineStringType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_LineString> LineString;
	struct LineString { typedef Iterator<gml::CLineStringType> iterator; };
	MemberElement<gml::COrientableCurveType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_OrientableCurve> OrientableCurve;
	struct OrientableCurve { typedef Iterator<gml::COrientableCurveType> iterator; };
	MemberElement<gml::COrientableSurfaceType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_OrientableSurface> OrientableSurface;
	struct OrientableSurface { typedef Iterator<gml::COrientableSurfaceType> iterator; };
	MemberElement<gml::CPointType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_Point> Point;
	struct Point { typedef Iterator<gml::CPointType> iterator; };
	MemberElement<gml::CPolygonType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_Polygon> Polygon;
	struct Polygon { typedef Iterator<gml::CPolygonType> iterator; };
	MemberElement<gml::CPolyhedralSurfaceType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_PolyhedralSurface> PolyhedralSurface;
	struct PolyhedralSurface { typedef Iterator<gml::CPolyhedralSurfaceType> iterator; };
	MemberElement<gml::CSolidType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_Solid> Solid;
	struct Solid { typedef Iterator<gml::CSolidType> iterator; };
	MemberElement<gml::CSurfaceType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_Surface> Surface;
	struct Surface { typedef Iterator<gml::CSurfaceType> iterator; };
	MemberElement<gml::CTinType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_Tin> Tin;
	struct Tin { typedef Iterator<gml::CTinType> iterator; };
	MemberElement<gml::CTriangulatedSurfaceType, _altova_mi_gml_altova_CGeometricPrimitivePropertyType_altova_TriangulatedSurface> TriangulatedSurface;
	struct TriangulatedSurface { typedef Iterator<gml::CTriangulatedSurfaceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricPrimitivePropertyType
