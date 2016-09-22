#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonPatchArrayPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonPatchArrayPropertyType



namespace gie
{

namespace gml
{	

class CPolygonPatchArrayPropertyType : public TypeBase
{
public:
	gie_EXPORT CPolygonPatchArrayPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CPolygonPatchArrayPropertyType(CPolygonPatchArrayPropertyType const& init);
	void operator=(CPolygonPatchArrayPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPolygonPatchArrayPropertyType); }
	MemberElement<gml::CConeType, _altova_mi_gml_altova_CPolygonPatchArrayPropertyType_altova_Cone> Cone;
	struct Cone { typedef Iterator<gml::CConeType> iterator; };
	MemberElement<gml::CCylinderType, _altova_mi_gml_altova_CPolygonPatchArrayPropertyType_altova_Cylinder> Cylinder;
	struct Cylinder { typedef Iterator<gml::CCylinderType> iterator; };
	MemberElement<gml::CPolygonPatchType, _altova_mi_gml_altova_CPolygonPatchArrayPropertyType_altova_PolygonPatch> PolygonPatch;
	struct PolygonPatch { typedef Iterator<gml::CPolygonPatchType> iterator; };
	MemberElement<gml::CRectangleType, _altova_mi_gml_altova_CPolygonPatchArrayPropertyType_altova_Rectangle> Rectangle;
	struct Rectangle { typedef Iterator<gml::CRectangleType> iterator; };
	MemberElement<gml::CSphereType, _altova_mi_gml_altova_CPolygonPatchArrayPropertyType_altova_Sphere> Sphere;
	struct Sphere { typedef Iterator<gml::CSphereType> iterator; };
	MemberElement<gml::CTriangleType, _altova_mi_gml_altova_CPolygonPatchArrayPropertyType_altova_Triangle> Triangle;
	struct Triangle { typedef Iterator<gml::CTriangleType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonPatchArrayPropertyType
