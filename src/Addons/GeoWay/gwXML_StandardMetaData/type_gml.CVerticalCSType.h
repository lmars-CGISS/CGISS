#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CVerticalCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CVerticalCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CVerticalCSType(CVerticalCSType const& init);
	void operator=(CVerticalCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CVerticalCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalCSType
