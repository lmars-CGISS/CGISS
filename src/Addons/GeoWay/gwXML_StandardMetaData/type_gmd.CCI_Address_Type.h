#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Address_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Address_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_Address_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_Address_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_Address_Type(CCI_Address_Type const& init);
	void operator=(CCI_Address_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_Address_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Address_Type_altova_deliveryPoint> deliveryPoint;
	struct deliveryPoint { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Address_Type_altova_city> city;
	struct city { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Address_Type_altova_administrativeArea> administrativeArea;
	struct administrativeArea { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Address_Type_altova_postalCode> postalCode;
	struct postalCode { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Address_Type_altova_country> country;
	struct country { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Address_Type_altova_electronicMailAddress> electronicMailAddress;
	struct electronicMailAddress { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Address_Type
