#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractEX_GeographicExtent_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractEX_GeographicExtent_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractEX_GeographicExtent_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractEX_GeographicExtent_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractEX_GeographicExtent_Type(CAbstractEX_GeographicExtent_Type const& init);
	void operator=(CAbstractEX_GeographicExtent_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractEX_GeographicExtent_Type); }
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CAbstractEX_GeographicExtent_Type_altova_extentTypeCode> extentTypeCode;
	struct extentTypeCode { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractEX_GeographicExtent_Type
