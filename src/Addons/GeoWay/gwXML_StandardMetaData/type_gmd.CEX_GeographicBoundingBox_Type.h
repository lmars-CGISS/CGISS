#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicBoundingBox_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicBoundingBox_Type

#include "type_gmd.CAbstractEX_GeographicExtent_Type.h"


namespace gie
{

namespace gmd
{	

class CEX_GeographicBoundingBox_Type : public ::gie::gmd::CAbstractEX_GeographicExtent_Type
{
public:
	gie_EXPORT CEX_GeographicBoundingBox_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CEX_GeographicBoundingBox_Type(CEX_GeographicBoundingBox_Type const& init);
	void operator=(CEX_GeographicBoundingBox_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CEX_GeographicBoundingBox_Type); }
	MemberElement<gco::CDecimal_PropertyType, _altova_mi_gmd_altova_CEX_GeographicBoundingBox_Type_altova_westBoundLongitude> westBoundLongitude;
	struct westBoundLongitude { typedef Iterator<gco::CDecimal_PropertyType> iterator; };
	MemberElement<gco::CDecimal_PropertyType, _altova_mi_gmd_altova_CEX_GeographicBoundingBox_Type_altova_eastBoundLongitude> eastBoundLongitude;
	struct eastBoundLongitude { typedef Iterator<gco::CDecimal_PropertyType> iterator; };
	MemberElement<gco::CDecimal_PropertyType, _altova_mi_gmd_altova_CEX_GeographicBoundingBox_Type_altova_southBoundLatitude> southBoundLatitude;
	struct southBoundLatitude { typedef Iterator<gco::CDecimal_PropertyType> iterator; };
	MemberElement<gco::CDecimal_PropertyType, _altova_mi_gmd_altova_CEX_GeographicBoundingBox_Type_altova_northBoundLatitude> northBoundLatitude;
	struct northBoundLatitude { typedef Iterator<gco::CDecimal_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicBoundingBox_Type
