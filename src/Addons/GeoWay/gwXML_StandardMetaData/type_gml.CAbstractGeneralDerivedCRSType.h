#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralDerivedCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralDerivedCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CAbstractGeneralDerivedCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CAbstractGeneralDerivedCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeneralDerivedCRSType(CAbstractGeneralDerivedCRSType const& init);
	void operator=(CAbstractGeneralDerivedCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeneralDerivedCRSType); }
	MemberElement<gml::CGeneralConversionPropertyType, _altova_mi_gml_altova_CAbstractGeneralDerivedCRSType_altova_conversion> conversion;
	struct conversion { typedef Iterator<gml::CGeneralConversionPropertyType> iterator; };
	MemberElement<gml::CGeneralConversionPropertyType, _altova_mi_gml_altova_CAbstractGeneralDerivedCRSType_altova_definedByConversion> definedByConversion;
	struct definedByConversion { typedef Iterator<gml::CGeneralConversionPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralDerivedCRSType
