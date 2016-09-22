#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CTimeType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CTimeType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeType(CTimeType const& init);
	void operator=(CTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeType
