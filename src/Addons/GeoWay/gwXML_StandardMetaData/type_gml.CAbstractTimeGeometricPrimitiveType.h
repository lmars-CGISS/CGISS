#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeGeometricPrimitiveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeGeometricPrimitiveType

#include "type_gml.CAbstractTimePrimitiveType.h"


namespace gie
{

namespace gml
{	

class CAbstractTimeGeometricPrimitiveType : public ::gie::gml::CAbstractTimePrimitiveType
{
public:
	gie_EXPORT CAbstractTimeGeometricPrimitiveType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTimeGeometricPrimitiveType(CAbstractTimeGeometricPrimitiveType const& init);
	void operator=(CAbstractTimeGeometricPrimitiveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTimeGeometricPrimitiveType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractTimeGeometricPrimitiveType_altova_frame, 0, 0> frame;	// frame CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeGeometricPrimitiveType
