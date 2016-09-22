#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTopologyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTopologyType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CAbstractTopologyType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CAbstractTopologyType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTopologyType(CAbstractTopologyType const& init);
	void operator=(CAbstractTopologyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTopologyType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTopologyType
