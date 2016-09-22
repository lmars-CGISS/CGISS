#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CBooleanType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CBooleanType

#include "type_xs.CbooleanType.h"


namespace gie
{

namespace gie2
{	

class CBooleanType : public ::gie::xs::CbooleanType
{
public:
	gie_EXPORT CBooleanType(xercesc::DOMNode* const& init);
	gie_EXPORT CBooleanType(CBooleanType const& init);
	void operator=(CBooleanType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CBooleanType); }
	gie_EXPORT void operator=(const bool& value);
	MemberAttribute<string_type,_altova_mi_gie2_altova_CBooleanType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CBooleanType
