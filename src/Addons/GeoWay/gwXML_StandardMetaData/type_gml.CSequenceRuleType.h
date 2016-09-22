#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSequenceRuleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSequenceRuleType

#include "type_gml.CSequenceRuleEnumerationType.h"


namespace gie
{

namespace gml
{	

class CSequenceRuleType : public ::gie::gml::CSequenceRuleEnumerationType
{
public:
	gie_EXPORT CSequenceRuleType(xercesc::DOMNode* const& init);
	gie_EXPORT CSequenceRuleType(CSequenceRuleType const& init);
	void operator=(CSequenceRuleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSequenceRuleType); }
	gie_EXPORT void operator=(const string_type& value);
	MemberAttribute<string_type,_altova_mi_gml_altova_CSequenceRuleType_altova_order, 0, 4> order;	// order CIncrementOrder

	MemberAttribute<string_type,_altova_mi_gml_altova_CSequenceRuleType_altova_axisOrder, 0, 0> axisOrder;	// axisOrder CAxisDirectionList
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSequenceRuleType
