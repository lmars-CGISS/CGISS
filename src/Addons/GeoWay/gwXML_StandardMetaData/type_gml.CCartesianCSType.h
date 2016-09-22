#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCartesianCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCartesianCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CCartesianCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CCartesianCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CCartesianCSType(CCartesianCSType const& init);
	void operator=(CCartesianCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCartesianCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCartesianCSType
