#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractDatumType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractDatumType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractDatumType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CAbstractDatumType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractDatumType(CAbstractDatumType const& init);
	void operator=(CAbstractDatumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractDatumType); }
	MemberElement<gie2::CdomainOfValidityType, _altova_mi_gml_altova_CAbstractDatumType_altova_domainOfValidity> domainOfValidity;
	struct domainOfValidity { typedef Iterator<gie2::CdomainOfValidityType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CAbstractDatumType_altova_scope> scope;
	struct scope { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CAbstractDatumType_altova_anchorDefinition> anchorDefinition;
	struct anchorDefinition { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CAbstractDatumType_altova_anchorPoint> anchorPoint;
	struct anchorPoint { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<xs::CdateType, _altova_mi_gml_altova_CAbstractDatumType_altova_realizationEpoch> realizationEpoch;
	struct realizationEpoch { typedef Iterator<xs::CdateType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractDatumType
