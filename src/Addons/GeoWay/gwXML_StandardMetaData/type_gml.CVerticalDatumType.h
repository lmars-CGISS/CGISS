#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalDatumType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalDatumType

#include "type_gml.CAbstractDatumType.h"


namespace gie
{

namespace gml
{	

class CVerticalDatumType : public ::gie::gml::CAbstractDatumType
{
public:
	gie_EXPORT CVerticalDatumType(xercesc::DOMNode* const& init);
	gie_EXPORT CVerticalDatumType(CVerticalDatumType const& init);
	void operator=(CVerticalDatumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CVerticalDatumType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVerticalDatumType
