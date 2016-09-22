#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeComplexType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeComplexType

#include "type_gml.CAbstractTimeObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractTimeComplexType : public ::gie::gml::CAbstractTimeObjectType
{
public:
	gie_EXPORT CAbstractTimeComplexType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTimeComplexType(CAbstractTimeComplexType const& init);
	void operator=(CAbstractTimeComplexType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTimeComplexType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeComplexType
