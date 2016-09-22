#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_TemporalExtent_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_TemporalExtent_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CEX_TemporalExtent_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CEX_TemporalExtent_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CEX_TemporalExtent_Type(CEX_TemporalExtent_Type const& init);
	void operator=(CEX_TemporalExtent_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CEX_TemporalExtent_Type); }
	MemberElement<gts::CTM_Primitive_PropertyType, _altova_mi_gmd_altova_CEX_TemporalExtent_Type_altova_extent> extent;
	struct extent { typedef Iterator<gts::CTM_Primitive_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_TemporalExtent_Type
