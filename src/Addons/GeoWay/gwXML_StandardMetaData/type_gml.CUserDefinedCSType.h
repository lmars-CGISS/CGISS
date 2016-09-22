#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUserDefinedCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUserDefinedCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CUserDefinedCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CUserDefinedCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CUserDefinedCSType(CUserDefinedCSType const& init);
	void operator=(CUserDefinedCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CUserDefinedCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUserDefinedCSType
