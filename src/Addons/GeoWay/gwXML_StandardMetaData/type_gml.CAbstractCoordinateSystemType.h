#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoordinateSystemType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoordinateSystemType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractCoordinateSystemType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CAbstractCoordinateSystemType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractCoordinateSystemType(CAbstractCoordinateSystemType const& init);
	void operator=(CAbstractCoordinateSystemType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractCoordinateSystemType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractCoordinateSystemType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CCoordinateSystemAxisPropertyType, _altova_mi_gml_altova_CAbstractCoordinateSystemType_altova_axis> axis;
	struct axis { typedef Iterator<gml::CCoordinateSystemAxisPropertyType> iterator; };
	MemberElement<gml::CCoordinateSystemAxisPropertyType, _altova_mi_gml_altova_CAbstractCoordinateSystemType_altova_usesAxis> usesAxis;
	struct usesAxis { typedef Iterator<gml::CCoordinateSystemAxisPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoordinateSystemType
