#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEllipsoidalCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEllipsoidalCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CEllipsoidalCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CEllipsoidalCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CEllipsoidalCSType(CEllipsoidalCSType const& init);
	void operator=(CEllipsoidalCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CEllipsoidalCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEllipsoidalCSType
