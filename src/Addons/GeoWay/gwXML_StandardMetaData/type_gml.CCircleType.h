#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCircleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCircleType

#include "type_gml.CArcType.h"


namespace gie
{

namespace gml
{	

class CCircleType : public ::gie::gml::CArcType
{
public:
	gie_EXPORT CCircleType(xercesc::DOMNode* const& init);
	gie_EXPORT CCircleType(CCircleType const& init);
	void operator=(CCircleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCircleType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCircleType
