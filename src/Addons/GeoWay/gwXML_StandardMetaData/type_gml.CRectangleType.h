#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRectangleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRectangleType

#include "type_gml.CAbstractSurfacePatchType.h"


namespace gie
{

namespace gml
{	

class CRectangleType : public ::gie::gml::CAbstractSurfacePatchType
{
public:
	gie_EXPORT CRectangleType(xercesc::DOMNode* const& init);
	gie_EXPORT CRectangleType(CRectangleType const& init);
	void operator=(CRectangleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRectangleType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CRectangleType_altova_interpolation, 0, 10> interpolation;	// interpolation CSurfaceInterpolationType
	MemberElement<gml::CAbstractRingPropertyType, _altova_mi_gml_altova_CRectangleType_altova_exterior> exterior;
	struct exterior { typedef Iterator<gml::CAbstractRingPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRectangleType
