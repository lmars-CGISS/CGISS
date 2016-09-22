#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometricAggregateType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometricAggregateType

#include "type_gml.CAbstractGeometryType.h"


namespace gie
{

namespace gml
{	

class CAbstractGeometricAggregateType : public ::gie::gml::CAbstractGeometryType
{
public:
	gie_EXPORT CAbstractGeometricAggregateType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeometricAggregateType(CAbstractGeometricAggregateType const& init);
	void operator=(CAbstractGeometricAggregateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeometricAggregateType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractGeometricAggregateType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometricAggregateType
