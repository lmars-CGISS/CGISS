#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyComplexType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyComplexType

#include "type_gml.CAbstractTimeComplexType.h"


namespace gie
{

namespace gml
{	

class CTimeTopologyComplexType : public ::gie::gml::CAbstractTimeComplexType
{
public:
	gie_EXPORT CTimeTopologyComplexType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeTopologyComplexType(CTimeTopologyComplexType const& init);
	void operator=(CTimeTopologyComplexType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeTopologyComplexType); }
	MemberElement<gml::CTimeTopologyPrimitivePropertyType, _altova_mi_gml_altova_CTimeTopologyComplexType_altova_primitive> primitive;
	struct primitive { typedef Iterator<gml::CTimeTopologyPrimitivePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeTopologyComplexType
