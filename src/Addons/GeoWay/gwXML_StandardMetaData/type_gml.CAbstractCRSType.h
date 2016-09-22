#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCRSType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractCRSType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CAbstractCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractCRSType(CAbstractCRSType const& init);
	void operator=(CAbstractCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractCRSType); }
	MemberElement<gie2::CdomainOfValidityType, _altova_mi_gml_altova_CAbstractCRSType_altova_domainOfValidity> domainOfValidity;
	struct domainOfValidity { typedef Iterator<gie2::CdomainOfValidityType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CAbstractCRSType_altova_scope> scope;
	struct scope { typedef Iterator<xs::CstringType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCRSType
