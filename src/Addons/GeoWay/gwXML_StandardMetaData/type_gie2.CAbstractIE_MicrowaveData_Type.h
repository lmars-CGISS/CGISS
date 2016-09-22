#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_MicrowaveData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_MicrowaveData_Type

#include "type_gie2.CAbstractIE_Imagery_Type.h"


namespace gie
{

namespace gie2
{	

class CAbstractIE_MicrowaveData_Type : public ::gie::gie2::CAbstractIE_Imagery_Type
{
public:
	gie_EXPORT CAbstractIE_MicrowaveData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractIE_MicrowaveData_Type(CAbstractIE_MicrowaveData_Type const& init);
	void operator=(CAbstractIE_MicrowaveData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CAbstractIE_MicrowaveData_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_MicrowaveData_Type
