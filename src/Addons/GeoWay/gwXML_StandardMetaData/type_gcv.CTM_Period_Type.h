#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_Period_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_Period_Type

#include "type_gml.CTimePeriodType.h"


namespace gie
{

namespace gcv
{	

class CTM_Period_Type : public ::gie::gml::CTimePeriodType
{
public:
	gie_EXPORT CTM_Period_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CTM_Period_Type(CTM_Period_Type const& init);
	void operator=(CTM_Period_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CTM_Period_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_Period_Type
