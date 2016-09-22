#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCategoryType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCategoryType

#include "type_gml.CCodeType.h"


namespace gie
{

namespace gie2
{	

class CCategoryType : public ::gie::gml::CCodeType
{
public:
	gie_EXPORT CCategoryType(xercesc::DOMNode* const& init);
	gie_EXPORT CCategoryType(CCategoryType const& init);
	void operator=(CCategoryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CCategoryType); }
	gie_EXPORT void operator=(const string_type& value);
	MemberAttribute<string_type,_altova_mi_gie2_altova_CCategoryType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CCategoryType
