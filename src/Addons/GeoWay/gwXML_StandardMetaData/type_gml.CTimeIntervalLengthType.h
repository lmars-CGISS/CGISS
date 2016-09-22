#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeIntervalLengthType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeIntervalLengthType

#include "type_xs.CdecimalType.h"


namespace gie
{

namespace gml
{	

class CTimeIntervalLengthType : public ::gie::xs::CdecimalType
{
public:
	gie_EXPORT CTimeIntervalLengthType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeIntervalLengthType(CTimeIntervalLengthType const& init);
	void operator=(CTimeIntervalLengthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeIntervalLengthType); }
	gie_EXPORT void operator=(const double& value);
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimeIntervalLengthType_altova_unit, 0, 6> unit;	// unit CTimeUnitType

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CTimeIntervalLengthType_altova_radix, 0, 0> radix;	// radix CpositiveInteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CTimeIntervalLengthType_altova_factor, 0, 0> factor;	// factor Cinteger
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeIntervalLengthType
