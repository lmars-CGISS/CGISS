#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPriorityLocationPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPriorityLocationPropertyType

#include "type_gml.CLocationPropertyType.h"


namespace gie
{

namespace gml
{	

class CPriorityLocationPropertyType : public ::gie::gml::CLocationPropertyType
{
public:
	gie_EXPORT CPriorityLocationPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CPriorityLocationPropertyType(CPriorityLocationPropertyType const& init);
	void operator=(CPriorityLocationPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPriorityLocationPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CPriorityLocationPropertyType_altova_priority, 0, 0> priority;	// priority Cstring
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPriorityLocationPropertyType
