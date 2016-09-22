#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAngleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAngleType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CAngleType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CAngleType(xercesc::DOMNode* const& init);
	gie_EXPORT CAngleType(CAngleType const& init);
	void operator=(CAngleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAngleType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAngleType
