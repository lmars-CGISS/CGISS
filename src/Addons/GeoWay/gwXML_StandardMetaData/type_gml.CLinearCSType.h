#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CLinearCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CLinearCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CLinearCSType(CLinearCSType const& init);
	void operator=(CLinearCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLinearCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearCSType
