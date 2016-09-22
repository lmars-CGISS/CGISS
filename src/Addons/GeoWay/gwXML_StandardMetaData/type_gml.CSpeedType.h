#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSpeedType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSpeedType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CSpeedType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CSpeedType(xercesc::DOMNode* const& init);
	gie_EXPORT CSpeedType(CSpeedType const& init);
	void operator=(CSpeedType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSpeedType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSpeedType
