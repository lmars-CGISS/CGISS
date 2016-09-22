#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_PositionalAccuracy_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_PositionalAccuracy_Type

#include "type_gmd.CAbstractDQ_Element_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractDQ_PositionalAccuracy_Type : public ::gie::gmd::CAbstractDQ_Element_Type
{
public:
	gie_EXPORT CAbstractDQ_PositionalAccuracy_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractDQ_PositionalAccuracy_Type(CAbstractDQ_PositionalAccuracy_Type const& init);
	void operator=(CAbstractDQ_PositionalAccuracy_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractDQ_PositionalAccuracy_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_PositionalAccuracy_Type
