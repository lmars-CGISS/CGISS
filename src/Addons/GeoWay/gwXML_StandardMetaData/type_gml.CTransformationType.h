#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTransformationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTransformationType

#include "type_gml.CAbstractGeneralTransformationType.h"


namespace gie
{

namespace gml
{	

class CTransformationType : public ::gie::gml::CAbstractGeneralTransformationType
{
public:
	gie_EXPORT CTransformationType(xercesc::DOMNode* const& init);
	gie_EXPORT CTransformationType(CTransformationType const& init);
	void operator=(CTransformationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTransformationType); }
	MemberElement<gml::COperationMethodPropertyType, _altova_mi_gml_altova_CTransformationType_altova_method> method;
	struct method { typedef Iterator<gml::COperationMethodPropertyType> iterator; };
	MemberElement<gml::COperationMethodPropertyType, _altova_mi_gml_altova_CTransformationType_altova_usesMethod> usesMethod;
	struct usesMethod { typedef Iterator<gml::COperationMethodPropertyType> iterator; };
	MemberElement<gml::CAbstractGeneralParameterValuePropertyType, _altova_mi_gml_altova_CTransformationType_altova_parameterValue> parameterValue;
	struct parameterValue { typedef Iterator<gml::CAbstractGeneralParameterValuePropertyType> iterator; };
	MemberElement<gml::CAbstractGeneralParameterValuePropertyType, _altova_mi_gml_altova_CTransformationType_altova_includesValue> includesValue;
	struct includesValue { typedef Iterator<gml::CAbstractGeneralParameterValuePropertyType> iterator; };
	MemberElement<gml::CAbstractGeneralParameterValuePropertyType, _altova_mi_gml_altova_CTransformationType_altova_usesValue> usesValue;
	struct usesValue { typedef Iterator<gml::CAbstractGeneralParameterValuePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTransformationType
