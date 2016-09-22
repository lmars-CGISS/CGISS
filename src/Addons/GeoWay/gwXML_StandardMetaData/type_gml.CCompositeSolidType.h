#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeSolidType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeSolidType

#include "type_gml.CAbstractSolidType.h"


namespace gie
{

namespace gml
{	

class CCompositeSolidType : public ::gie::gml::CAbstractSolidType
{
public:
	gie_EXPORT CCompositeSolidType(xercesc::DOMNode* const& init);
	gie_EXPORT CCompositeSolidType(CCompositeSolidType const& init);
	void operator=(CCompositeSolidType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCompositeSolidType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CCompositeSolidType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CSolidPropertyType, _altova_mi_gml_altova_CCompositeSolidType_altova_solidMember> solidMember;
	struct solidMember { typedef Iterator<gml::CSolidPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompositeSolidType
