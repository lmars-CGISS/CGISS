#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAreaType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAreaType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CAreaType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CAreaType(xercesc::DOMNode* const& init);
	gie_EXPORT CAreaType(CAreaType const& init);
	void operator=(CAreaType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAreaType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAreaType
