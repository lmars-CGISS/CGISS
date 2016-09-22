#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeObjectType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeObjectType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CAbstractTimeObjectType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CAbstractTimeObjectType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTimeObjectType(CAbstractTimeObjectType const& init);
	void operator=(CAbstractTimeObjectType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTimeObjectType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeObjectType
