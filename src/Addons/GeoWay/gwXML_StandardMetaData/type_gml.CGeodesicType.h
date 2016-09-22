#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodesicType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodesicType

#include "type_gml.CGeodesicStringType.h"


namespace gie
{

namespace gml
{	

class CGeodesicType : public ::gie::gml::CGeodesicStringType
{
public:
	gie_EXPORT CGeodesicType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeodesicType(CGeodesicType const& init);
	void operator=(CGeodesicType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeodesicType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeodesicType
