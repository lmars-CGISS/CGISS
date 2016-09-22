#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonPatchType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonPatchType

#include "type_gml.CAbstractSurfacePatchType.h"


namespace gie
{

namespace gml
{	

class CPolygonPatchType : public ::gie::gml::CAbstractSurfacePatchType
{
public:
	gie_EXPORT CPolygonPatchType(xercesc::DOMNode* const& init);
	gie_EXPORT CPolygonPatchType(CPolygonPatchType const& init);
	void operator=(CPolygonPatchType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPolygonPatchType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CPolygonPatchType_altova_interpolation, 0, 10> interpolation;	// interpolation CSurfaceInterpolationType
	MemberElement<gml::CAbstractRingPropertyType, _altova_mi_gml_altova_CPolygonPatchType_altova_exterior> exterior;
	struct exterior { typedef Iterator<gml::CAbstractRingPropertyType> iterator; };
	MemberElement<gml::CAbstractRingPropertyType, _altova_mi_gml_altova_CPolygonPatchType_altova_interior> interior;
	struct interior { typedef Iterator<gml::CAbstractRingPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonPatchType
