#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoordinateOperationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoordinateOperationType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractCoordinateOperationType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CAbstractCoordinateOperationType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractCoordinateOperationType(CAbstractCoordinateOperationType const& init);
	void operator=(CAbstractCoordinateOperationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractCoordinateOperationType); }
	MemberElement<gie2::CdomainOfValidityType, _altova_mi_gml_altova_CAbstractCoordinateOperationType_altova_domainOfValidity> domainOfValidity;
	struct domainOfValidity { typedef Iterator<gie2::CdomainOfValidityType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CAbstractCoordinateOperationType_altova_scope> scope;
	struct scope { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CAbstractCoordinateOperationType_altova_operationVersion> operationVersion;
	struct operationVersion { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<gie2::CcoordinateOperationAccuracyType, _altova_mi_gml_altova_CAbstractCoordinateOperationType_altova_coordinateOperationAccuracy> coordinateOperationAccuracy;
	struct coordinateOperationAccuracy { typedef Iterator<gie2::CcoordinateOperationAccuracyType> iterator; };
	MemberElement<gml::CCRSPropertyType, _altova_mi_gml_altova_CAbstractCoordinateOperationType_altova_sourceCRS> sourceCRS;
	struct sourceCRS { typedef Iterator<gml::CCRSPropertyType> iterator; };
	MemberElement<gml::CCRSPropertyType, _altova_mi_gml_altova_CAbstractCoordinateOperationType_altova_targetCRS> targetCRS;
	struct targetCRS { typedef Iterator<gml::CCRSPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoordinateOperationType
