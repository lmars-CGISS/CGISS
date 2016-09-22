#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CScaleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CScaleType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CScaleType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CScaleType(xercesc::DOMNode* const& init);
	gie_EXPORT CScaleType(CScaleType const& init);
	void operator=(CScaleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CScaleType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CScaleType
