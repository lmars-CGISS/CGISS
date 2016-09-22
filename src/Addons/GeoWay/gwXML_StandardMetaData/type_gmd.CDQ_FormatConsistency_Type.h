#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_FormatConsistency_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_FormatConsistency_Type

#include "type_gmd.CAbstractDQ_LogicalConsistency_Type.h"


namespace gie
{

namespace gmd
{	

class CDQ_FormatConsistency_Type : public ::gie::gmd::CAbstractDQ_LogicalConsistency_Type
{
public:
	gie_EXPORT CDQ_FormatConsistency_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CDQ_FormatConsistency_Type(CDQ_FormatConsistency_Type const& init);
	void operator=(CDQ_FormatConsistency_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDQ_FormatConsistency_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_FormatConsistency_Type
