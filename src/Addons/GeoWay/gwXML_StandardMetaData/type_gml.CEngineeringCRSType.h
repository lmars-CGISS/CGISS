#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEngineeringCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEngineeringCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CEngineeringCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CEngineeringCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CEngineeringCRSType(CEngineeringCRSType const& init);
	void operator=(CEngineeringCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CEngineeringCRSType); }
	MemberElement<gml::CCoordinateSystemPropertyType, _altova_mi_gml_altova_CEngineeringCRSType_altova_coordinateSystem> coordinateSystem;
	struct coordinateSystem { typedef Iterator<gml::CCoordinateSystemPropertyType> iterator; };
	MemberElement<gml::CCoordinateSystemPropertyType, _altova_mi_gml_altova_CEngineeringCRSType_altova_usesCS> usesCS;
	struct usesCS { typedef Iterator<gml::CCoordinateSystemPropertyType> iterator; };
	MemberElement<gml::CEngineeringDatumPropertyType, _altova_mi_gml_altova_CEngineeringCRSType_altova_engineeringDatum> engineeringDatum;
	struct engineeringDatum { typedef Iterator<gml::CEngineeringDatumPropertyType> iterator; };
	MemberElement<gml::CEngineeringDatumPropertyType, _altova_mi_gml_altova_CEngineeringCRSType_altova_usesEngineeringDatum> usesEngineeringDatum;
	struct usesEngineeringDatum { typedef Iterator<gml::CEngineeringDatumPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEngineeringCRSType
