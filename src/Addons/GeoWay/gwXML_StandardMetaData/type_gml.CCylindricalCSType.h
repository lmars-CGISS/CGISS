#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCylindricalCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCylindricalCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CCylindricalCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CCylindricalCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CCylindricalCSType(CCylindricalCSType const& init);
	void operator=(CCylindricalCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCylindricalCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCylindricalCSType
