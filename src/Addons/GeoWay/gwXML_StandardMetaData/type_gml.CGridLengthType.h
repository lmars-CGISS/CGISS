#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridLengthType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridLengthType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CGridLengthType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CGridLengthType(xercesc::DOMNode* const& init);
	gie_EXPORT CGridLengthType(CGridLengthType const& init);
	void operator=(CGridLengthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGridLengthType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridLengthType
