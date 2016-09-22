#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricComplexType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricComplexType

#include "type_gml.CAbstractGeometryType.h"


namespace gie
{

namespace gml
{	

class CGeometricComplexType : public ::gie::gml::CAbstractGeometryType
{
public:
	gie_EXPORT CGeometricComplexType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeometricComplexType(CGeometricComplexType const& init);
	void operator=(CGeometricComplexType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeometricComplexType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CGeometricPrimitivePropertyType, _altova_mi_gml_altova_CGeometricComplexType_altova_element> element;
	struct element { typedef Iterator<gml::CGeometricPrimitivePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricComplexType
