#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_GeometricPrimitive_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_GeometricPrimitive_Type

#include "type_gml.CAbstractTimeGeometricPrimitiveType.h"


namespace gie
{

namespace gcv
{	

class CTM_GeometricPrimitive_Type : public ::gie::gml::CAbstractTimeGeometricPrimitiveType
{
public:
	gie_EXPORT CTM_GeometricPrimitive_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CTM_GeometricPrimitive_Type(CTM_GeometricPrimitive_Type const& init);
	void operator=(CTM_GeometricPrimitive_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CTM_GeometricPrimitive_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_GeometricPrimitive_Type
