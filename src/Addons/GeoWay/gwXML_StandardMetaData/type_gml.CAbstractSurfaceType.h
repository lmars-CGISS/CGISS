#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSurfaceType

#include "type_gml.CAbstractGeometricPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CAbstractSurfaceType : public ::gie::gml::CAbstractGeometricPrimitiveType
{
public:
	gie_EXPORT CAbstractSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractSurfaceType(CAbstractSurfaceType const& init);
	void operator=(CAbstractSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractSurfaceType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSurfaceType
