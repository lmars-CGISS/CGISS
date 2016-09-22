#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoComplexType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoComplexType

#include "type_gml.CAbstractTopologyType.h"


namespace gie
{

namespace gml
{	

class CTopoComplexType : public ::gie::gml::CAbstractTopologyType
{
public:
	gie_EXPORT CTopoComplexType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoComplexType(CTopoComplexType const& init);
	void operator=(CTopoComplexType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoComplexType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CTopoComplexType_altova_isMaximal, 0, 0> isMaximal;	// isMaximal Cboolean
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoComplexType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CTopoComplexMemberType, _altova_mi_gml_altova_CTopoComplexType_altova_maximalComplex> maximalComplex;
	struct maximalComplex { typedef Iterator<gml::CTopoComplexMemberType> iterator; };
	MemberElement<gml::CTopoComplexMemberType, _altova_mi_gml_altova_CTopoComplexType_altova_superComplex> superComplex;
	struct superComplex { typedef Iterator<gml::CTopoComplexMemberType> iterator; };
	MemberElement<gml::CTopoComplexMemberType, _altova_mi_gml_altova_CTopoComplexType_altova_subComplex> subComplex;
	struct subComplex { typedef Iterator<gml::CTopoComplexMemberType> iterator; };
	MemberElement<gml::CTopoPrimitiveMemberType, _altova_mi_gml_altova_CTopoComplexType_altova_topoPrimitiveMember> topoPrimitiveMember;
	struct topoPrimitiveMember { typedef Iterator<gml::CTopoPrimitiveMemberType> iterator; };
	MemberElement<gml::CTopoPrimitiveArrayAssociationType, _altova_mi_gml_altova_CTopoComplexType_altova_topoPrimitiveMembers> topoPrimitiveMembers;
	struct topoPrimitiveMembers { typedef Iterator<gml::CTopoPrimitiveArrayAssociationType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoComplexType
