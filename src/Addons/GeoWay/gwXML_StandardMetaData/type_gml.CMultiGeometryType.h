#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiGeometryType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiGeometryType

#include "type_gml.CAbstractGeometricAggregateType.h"


namespace gie
{

namespace gml
{	

class CMultiGeometryType : public ::gie::gml::CAbstractGeometricAggregateType
{
public:
	gie_EXPORT CMultiGeometryType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiGeometryType(CMultiGeometryType const& init);
	void operator=(CMultiGeometryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiGeometryType); }
	MemberElement<gml::CGeometryPropertyType, _altova_mi_gml_altova_CMultiGeometryType_altova_geometryMember> geometryMember;
	struct geometryMember { typedef Iterator<gml::CGeometryPropertyType> iterator; };
	MemberElement<gml::CGeometryArrayPropertyType, _altova_mi_gml_altova_CMultiGeometryType_altova_geometryMembers> geometryMembers;
	struct geometryMembers { typedef Iterator<gml::CGeometryArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiGeometryType
