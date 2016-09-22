#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeographicCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeographicCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CGeographicCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CGeographicCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeographicCRSType(CGeographicCRSType const& init);
	void operator=(CGeographicCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeographicCRSType); }
	MemberElement<gml::CEllipsoidalCSPropertyType, _altova_mi_gml_altova_CGeographicCRSType_altova_usesEllipsoidalCS> usesEllipsoidalCS;
	struct usesEllipsoidalCS { typedef Iterator<gml::CEllipsoidalCSPropertyType> iterator; };
	MemberElement<gml::CGeodeticDatumPropertyType, _altova_mi_gml_altova_CGeographicCRSType_altova_usesGeodeticDatum> usesGeodeticDatum;
	struct usesGeodeticDatum { typedef Iterator<gml::CGeodeticDatumPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeographicCRSType
