#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CVerticalCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CVerticalCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CVerticalCRSType(CVerticalCRSType const& init);
	void operator=(CVerticalCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CVerticalCRSType); }
	MemberElement<gml::CVerticalCSPropertyType, _altova_mi_gml_altova_CVerticalCRSType_altova_verticalCS> verticalCS;
	struct verticalCS { typedef Iterator<gml::CVerticalCSPropertyType> iterator; };
	MemberElement<gml::CVerticalCSPropertyType, _altova_mi_gml_altova_CVerticalCRSType_altova_usesVerticalCS> usesVerticalCS;
	struct usesVerticalCS { typedef Iterator<gml::CVerticalCSPropertyType> iterator; };
	MemberElement<gml::CVerticalDatumPropertyType, _altova_mi_gml_altova_CVerticalCRSType_altova_verticalDatum> verticalDatum;
	struct verticalDatum { typedef Iterator<gml::CVerticalDatumPropertyType> iterator; };
	MemberElement<gml::CVerticalDatumPropertyType, _altova_mi_gml_altova_CVerticalCRSType_altova_usesVerticalDatum> usesVerticalDatum;
	struct usesVerticalDatum { typedef Iterator<gml::CVerticalDatumPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalCRSType
