#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLengthType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLengthType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CLengthType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CLengthType(xercesc::DOMNode* const& init);
	gie_EXPORT CLengthType(CLengthType const& init);
	void operator=(CLengthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLengthType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLengthType
