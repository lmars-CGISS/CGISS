#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSphericalCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSphericalCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CSphericalCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CSphericalCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CSphericalCSType(CSphericalCSType const& init);
	void operator=(CSphericalCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSphericalCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSphericalCSType
