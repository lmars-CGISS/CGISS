#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_SpatialTemporalExtent_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_SpatialTemporalExtent_Type

#include "type_gmd.CEX_TemporalExtent_Type.h"


namespace gie
{

namespace gmd
{	

class CEX_SpatialTemporalExtent_Type : public ::gie::gmd::CEX_TemporalExtent_Type
{
public:
	gie_EXPORT CEX_SpatialTemporalExtent_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CEX_SpatialTemporalExtent_Type(CEX_SpatialTemporalExtent_Type const& init);
	void operator=(CEX_SpatialTemporalExtent_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CEX_SpatialTemporalExtent_Type); }
	MemberElement<gmd::CEX_GeographicExtent_PropertyType, _altova_mi_gmd_altova_CEX_SpatialTemporalExtent_Type_altova_spatialExtent> spatialExtent;
	struct spatialExtent { typedef Iterator<gmd::CEX_GeographicExtent_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_SpatialTemporalExtent_Type
