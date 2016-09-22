#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CParameterValueGroupType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CParameterValueGroupType

#include "type_gml.CAbstractGeneralParameterValueType.h"


namespace gie
{

namespace gml
{	

class CParameterValueGroupType : public ::gie::gml::CAbstractGeneralParameterValueType
{
public:
	gie_EXPORT CParameterValueGroupType(xercesc::DOMNode* const& init);
	gie_EXPORT CParameterValueGroupType(CParameterValueGroupType const& init);
	void operator=(CParameterValueGroupType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CParameterValueGroupType); }
	MemberElement<gml::CAbstractGeneralParameterValuePropertyType, _altova_mi_gml_altova_CParameterValueGroupType_altova_parameterValue> parameterValue;
	struct parameterValue { typedef Iterator<gml::CAbstractGeneralParameterValuePropertyType> iterator; };
	MemberElement<gml::CAbstractGeneralParameterValuePropertyType, _altova_mi_gml_altova_CParameterValueGroupType_altova_includesValue> includesValue;
	struct includesValue { typedef Iterator<gml::CAbstractGeneralParameterValuePropertyType> iterator; };
	MemberElement<gml::CAbstractGeneralParameterValuePropertyType, _altova_mi_gml_altova_CParameterValueGroupType_altova_usesValue> usesValue;
	struct usesValue { typedef Iterator<gml::CAbstractGeneralParameterValuePropertyType> iterator; };
	MemberElement<gml::COperationParameterGroupPropertyType, _altova_mi_gml_altova_CParameterValueGroupType_altova_group> group;
	struct group { typedef Iterator<gml::COperationParameterGroupPropertyType> iterator; };
	MemberElement<gml::COperationParameterGroupPropertyType, _altova_mi_gml_altova_CParameterValueGroupType_altova_valuesOfGroup> valuesOfGroup;
	struct valuesOfGroup { typedef Iterator<gml::COperationParameterGroupPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CParameterValueGroupType
