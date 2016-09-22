#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_ProductionSeries_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_ProductionSeries_Type

#include "type_gmd.CDS_Series_Type.h"


namespace gie
{

namespace gmd
{	

class CDS_ProductionSeries_Type : public ::gie::gmd::CDS_Series_Type
{
public:
	gie_EXPORT CDS_ProductionSeries_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CDS_ProductionSeries_Type(CDS_ProductionSeries_Type const& init);
	void operator=(CDS_ProductionSeries_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDS_ProductionSeries_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_ProductionSeries_Type
