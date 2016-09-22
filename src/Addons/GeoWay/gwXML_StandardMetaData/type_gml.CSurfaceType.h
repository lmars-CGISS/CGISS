#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfaceType

#include "type_gml.CAbstractSurfaceType.h"


namespace gie
{

namespace gml
{	

class CSurfaceType : public ::gie::gml::CAbstractSurfaceType
{
public:
	gie_EXPORT CSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CSurfaceType(CSurfaceType const& init);
	void operator=(CSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSurfaceType); }
	MemberElement<gml::CSurfacePatchArrayPropertyType, _altova_mi_gml_altova_CSurfaceType_altova_patches> patches;
	struct patches { typedef Iterator<gml::CSurfacePatchArrayPropertyType> iterator; };
	MemberElement<gml::CPolygonPatchArrayPropertyType, _altova_mi_gml_altova_CSurfaceType_altova_polygonPatches> polygonPatches;
	struct polygonPatches { typedef Iterator<gml::CPolygonPatchArrayPropertyType> iterator; };
	MemberElement<gml::CTrianglePatchArrayPropertyType, _altova_mi_gml_altova_CSurfaceType_altova_trianglePatches> trianglePatches;
	struct trianglePatches { typedef Iterator<gml::CTrianglePatchArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfaceType
