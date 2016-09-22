#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSolidType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSolidType

#include "type_gml.CAbstractGeometricPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CAbstractSolidType : public ::gie::gml::CAbstractGeometricPrimitiveType
{
public:
	gie_EXPORT CAbstractSolidType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractSolidType(CAbstractSolidType const& init);
	void operator=(CAbstractSolidType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractSolidType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSolidType
