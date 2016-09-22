#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidType

#include "type_gml.CAbstractGeometricAggregateType.h"


namespace gie
{

namespace gml
{	

class CMultiSolidType : public ::gie::gml::CAbstractGeometricAggregateType
{
public:
	gie_EXPORT CMultiSolidType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiSolidType(CMultiSolidType const& init);
	void operator=(CMultiSolidType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiSolidType); }
	MemberElement<gml::CSolidPropertyType, _altova_mi_gml_altova_CMultiSolidType_altova_solidMember> solidMember;
	struct solidMember { typedef Iterator<gml::CSolidPropertyType> iterator; };
	MemberElement<gml::CSolidArrayPropertyType, _altova_mi_gml_altova_CMultiSolidType_altova_solidMembers> solidMembers;
	struct solidMembers { typedef Iterator<gml::CSolidArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidType
