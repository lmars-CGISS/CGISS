#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeReferenceSystemType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeReferenceSystemType

#include "type_gml.CDefinitionType.h"


namespace gie
{

namespace gml
{	

class CTimeReferenceSystemType : public ::gie::gml::CDefinitionType
{
public:
	gie_EXPORT CTimeReferenceSystemType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeReferenceSystemType(CTimeReferenceSystemType const& init);
	void operator=(CTimeReferenceSystemType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeReferenceSystemType); }
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CTimeReferenceSystemType_altova_domainOfValidity> domainOfValidity;
	struct domainOfValidity { typedef Iterator<xs::CstringType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeReferenceSystemType
