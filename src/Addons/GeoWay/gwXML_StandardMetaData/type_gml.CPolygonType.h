#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonType

#include "type_gml.CAbstractSurfaceType.h"


namespace gie
{

namespace gml
{	

class CPolygonType : public ::gie::gml::CAbstractSurfaceType
{
public:
	gie_EXPORT CPolygonType(xercesc::DOMNode* const& init);
	gie_EXPORT CPolygonType(CPolygonType const& init);
	void operator=(CPolygonType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPolygonType); }
	MemberElement<gml::CAbstractRingPropertyType, _altova_mi_gml_altova_CPolygonType_altova_exterior> exterior;
	struct exterior { typedef Iterator<gml::CAbstractRingPropertyType> iterator; };
	MemberElement<gml::CAbstractRingPropertyType, _altova_mi_gml_altova_CPolygonType_altova_interior> interior;
	struct interior { typedef Iterator<gml::CAbstractRingPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolygonType
