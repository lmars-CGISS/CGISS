#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCountType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCountType

#include "type_xs.CintegerType.h"


namespace gie
{

namespace gie2
{	

class CCountType : public ::gie::xs::CintegerType
{
public:
	gie_EXPORT CCountType(xercesc::DOMNode* const& init);
	gie_EXPORT CCountType(CCountType const& init);
	void operator=(CCountType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CCountType); }
	gie_EXPORT void operator=(const __int64& value);
	MemberAttribute<string_type,_altova_mi_gie2_altova_CCountType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCountType
