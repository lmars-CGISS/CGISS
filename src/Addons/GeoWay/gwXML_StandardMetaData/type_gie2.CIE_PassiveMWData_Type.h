#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PassiveMWData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PassiveMWData_Type

#include "type_gie2.CAbstractIE_MicrowaveData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_PassiveMWData_Type : public ::gie::gie2::CAbstractIE_MicrowaveData_Type
{
public:
	gie_EXPORT CIE_PassiveMWData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_PassiveMWData_Type(CIE_PassiveMWData_Type const& init);
	void operator=(CIE_PassiveMWData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_PassiveMWData_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PassiveMWData_Type
