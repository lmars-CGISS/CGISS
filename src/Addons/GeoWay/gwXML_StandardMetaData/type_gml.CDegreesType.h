#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDegreesType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDegreesType

#include "type_gml.CDegreeValueTypeType.h"


namespace gie
{

namespace gml
{	

class CDegreesType : public ::gie::gml::CDegreeValueTypeType
{
public:
	gie_EXPORT CDegreesType(xercesc::DOMNode* const& init);
	gie_EXPORT CDegreesType(CDegreesType const& init);
	void operator=(CDegreesType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDegreesType); }
	gie_EXPORT void operator=(const unsigned __int64& value);
	MemberAttribute<string_type,_altova_mi_gml_altova_CDegreesType_altova_direction, 0, 6> direction;	// direction CdirectionType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDegreesType
