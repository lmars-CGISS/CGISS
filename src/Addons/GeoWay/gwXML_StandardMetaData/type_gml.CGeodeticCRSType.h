#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodeticCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodeticCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CGeodeticCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CGeodeticCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeodeticCRSType(CGeodeticCRSType const& init);
	void operator=(CGeodeticCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeodeticCRSType); }
	MemberElement<gml::CEllipsoidalCSPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_ellipsoidalCS> ellipsoidalCS;
	struct ellipsoidalCS { typedef Iterator<gml::CEllipsoidalCSPropertyType> iterator; };
	MemberElement<gml::CEllipsoidalCSPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_usesEllipsoidalCS> usesEllipsoidalCS;
	struct usesEllipsoidalCS { typedef Iterator<gml::CEllipsoidalCSPropertyType> iterator; };
	MemberElement<gml::CCartesianCSPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_cartesianCS> cartesianCS;
	struct cartesianCS { typedef Iterator<gml::CCartesianCSPropertyType> iterator; };
	MemberElement<gml::CCartesianCSPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_usesCartesianCS> usesCartesianCS;
	struct usesCartesianCS { typedef Iterator<gml::CCartesianCSPropertyType> iterator; };
	MemberElement<gml::CSphericalCSPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_sphericalCS> sphericalCS;
	struct sphericalCS { typedef Iterator<gml::CSphericalCSPropertyType> iterator; };
	MemberElement<gml::CSphericalCSPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_usesSphericalCS> usesSphericalCS;
	struct usesSphericalCS { typedef Iterator<gml::CSphericalCSPropertyType> iterator; };
	MemberElement<gml::CGeodeticDatumPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_geodeticDatum> geodeticDatum;
	struct geodeticDatum { typedef Iterator<gml::CGeodeticDatumPropertyType> iterator; };
	MemberElement<gml::CGeodeticDatumPropertyType, _altova_mi_gml_altova_CGeodeticCRSType_altova_usesGeodeticDatum> usesGeodeticDatum;
	struct usesGeodeticDatum { typedef Iterator<gml::CGeodeticDatumPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodeticCRSType
