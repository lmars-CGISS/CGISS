#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCurveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCurveType

#include "type_gml.CAbstractGeometricPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CAbstractCurveType : public ::gie::gml::CAbstractGeometricPrimitiveType
{
public:
	gie_EXPORT CAbstractCurveType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractCurveType(CAbstractCurveType const& init);
	void operator=(CAbstractCurveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractCurveType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCurveType
