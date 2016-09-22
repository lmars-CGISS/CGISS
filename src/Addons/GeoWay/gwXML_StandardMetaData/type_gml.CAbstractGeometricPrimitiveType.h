#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometricPrimitiveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometricPrimitiveType

#include "type_gml.CAbstractGeometryType.h"


namespace gie
{

namespace gml
{	

class CAbstractGeometricPrimitiveType : public ::gie::gml::CAbstractGeometryType
{
public:
	gie_EXPORT CAbstractGeometricPrimitiveType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeometricPrimitiveType(CAbstractGeometricPrimitiveType const& init);
	void operator=(CAbstractGeometricPrimitiveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeometricPrimitiveType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometricPrimitiveType
