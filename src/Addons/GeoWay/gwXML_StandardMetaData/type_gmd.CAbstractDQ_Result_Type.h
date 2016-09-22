#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_Result_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_Result_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractDQ_Result_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractDQ_Result_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractDQ_Result_Type(CAbstractDQ_Result_Type const& init);
	void operator=(CAbstractDQ_Result_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractDQ_Result_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_Result_Type
