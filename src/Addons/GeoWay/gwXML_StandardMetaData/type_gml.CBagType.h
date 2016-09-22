#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBagType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBagType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CBagType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CBagType(xercesc::DOMNode* const& init);
	gie_EXPORT CBagType(CBagType const& init);
	void operator=(CBagType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CBagType); }
	MemberElement<gml::CAssociationRoleType, _altova_mi_gml_altova_CBagType_altova_member> member;
	struct member { typedef Iterator<gml::CAssociationRoleType> iterator; };
	MemberElement<gml::CArrayAssociationType, _altova_mi_gml_altova_CBagType_altova_members> members;
	struct members { typedef Iterator<gml::CArrayAssociationType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBagType
