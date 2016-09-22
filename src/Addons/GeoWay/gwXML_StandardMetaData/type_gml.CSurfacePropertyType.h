#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfacePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfacePropertyType



namespace gie
{

namespace gml
{	

class CSurfacePropertyType : public TypeBase
{
public:
	gie_EXPORT CSurfacePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CSurfacePropertyType(CSurfacePropertyType const& init);
	void operator=(CSurfacePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSurfacePropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CSurfacePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CSurfacePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CCompositeSurfaceType, _altova_mi_gml_altova_CSurfacePropertyType_altova_CompositeSurface> CompositeSurface;
	struct CompositeSurface { typedef Iterator<gml::CCompositeSurfaceType> iterator; };
	MemberElement<gml::COrientableSurfaceType, _altova_mi_gml_altova_CSurfacePropertyType_altova_OrientableSurface> OrientableSurface;
	struct OrientableSurface { typedef Iterator<gml::COrientableSurfaceType> iterator; };
	MemberElement<gml::CPolygonType, _altova_mi_gml_altova_CSurfacePropertyType_altova_Polygon> Polygon;
	struct Polygon { typedef Iterator<gml::CPolygonType> iterator; };
	MemberElement<gml::CPolyhedralSurfaceType, _altova_mi_gml_altova_CSurfacePropertyType_altova_PolyhedralSurface> PolyhedralSurface;
	struct PolyhedralSurface { typedef Iterator<gml::CPolyhedralSurfaceType> iterator; };
	MemberElement<gml::CSurfaceType, _altova_mi_gml_altova_CSurfacePropertyType_altova_Surface> Surface;
	struct Surface { typedef Iterator<gml::CSurfaceType> iterator; };
	MemberElement<gml::CTinType, _altova_mi_gml_altova_CSurfacePropertyType_altova_Tin> Tin;
	struct Tin { typedef Iterator<gml::CTinType> iterator; };
	MemberElement<gml::CTriangulatedSurfaceType, _altova_mi_gml_altova_CSurfacePropertyType_altova_TriangulatedSurface> TriangulatedSurface;
	struct TriangulatedSurface { typedef Iterator<gml::CTriangulatedSurfaceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfacePropertyType
