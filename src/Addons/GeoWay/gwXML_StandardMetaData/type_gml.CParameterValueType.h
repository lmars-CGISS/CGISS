#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CParameterValueType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CParameterValueType

#include "type_gml.CAbstractGeneralParameterValueType.h"


namespace gie
{

namespace gml
{	

class CParameterValueType : public ::gie::gml::CAbstractGeneralParameterValueType
{
public:
	gie_EXPORT CParameterValueType(xercesc::DOMNode* const& init);
	gie_EXPORT CParameterValueType(CParameterValueType const& init);
	void operator=(CParameterValueType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CParameterValueType); }
	MemberElement<gml::CMeasureType, _altova_mi_gml_altova_CParameterValueType_altova_value2> value2;
	struct value2 { typedef Iterator<gml::CMeasureType> iterator; };
	MemberElement<gml::CDMSAngleType, _altova_mi_gml_altova_CParameterValueType_altova_dmsAngleValue> dmsAngleValue;
	struct dmsAngleValue { typedef Iterator<gml::CDMSAngleType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CParameterValueType_altova_stringValue> stringValue;
	struct stringValue { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CpositiveIntegerType, _altova_mi_gml_altova_CParameterValueType_altova_integerValue> integerValue;
	struct integerValue { typedef Iterator<xs::CpositiveIntegerType> iterator; };
	MemberElement<xs::CbooleanType, _altova_mi_gml_altova_CParameterValueType_altova_booleanValue> booleanValue;
	struct booleanValue { typedef Iterator<xs::CbooleanType> iterator; };
	MemberElement<gml::CMeasureListType, _altova_mi_gml_altova_CParameterValueType_altova_valueList> valueList;
	struct valueList { typedef Iterator<gml::CMeasureListType> iterator; };
	MemberElement<gml::CintegerListType, _altova_mi_gml_altova_CParameterValueType_altova_integerValueList> integerValueList;
	struct integerValueList { typedef Iterator<gml::CintegerListType> iterator; };
	MemberElement<xs::CanyURIType, _altova_mi_gml_altova_CParameterValueType_altova_valueFile> valueFile;
	struct valueFile { typedef Iterator<xs::CanyURIType> iterator; };
	MemberElement<gml::COperationParameterPropertyType, _altova_mi_gml_altova_CParameterValueType_altova_operationParameter> operationParameter;
	struct operationParameter { typedef Iterator<gml::COperationParameterPropertyType> iterator; };
	MemberElement<gml::COperationParameterPropertyType, _altova_mi_gml_altova_CParameterValueType_altova_valueOfParameter> valueOfParameter;
	struct valueOfParameter { typedef Iterator<gml::COperationParameterPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CParameterValueType
