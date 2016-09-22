#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolarCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolarCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CPolarCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CPolarCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CPolarCSType(CPolarCSType const& init);
	void operator=(CPolarCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPolarCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPolarCSType
