#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiPointType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiPointType

#include "type_gml.CAbstractGeometricAggregateType.h"


namespace gie
{

namespace gml
{	

class CMultiPointType : public ::gie::gml::CAbstractGeometricAggregateType
{
public:
	gie_EXPORT CMultiPointType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiPointType(CMultiPointType const& init);
	void operator=(CMultiPointType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiPointType); }
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CMultiPointType_altova_pointMember> pointMember;
	struct pointMember { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CPointArrayPropertyType, _altova_mi_gml_altova_CMultiPointType_altova_pointMembers> pointMembers;
	struct pointMembers { typedef Iterator<gml::CPointArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiPointType
