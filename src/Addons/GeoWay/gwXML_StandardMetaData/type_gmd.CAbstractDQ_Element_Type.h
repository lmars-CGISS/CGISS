#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_Element_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_Element_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractDQ_Element_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractDQ_Element_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractDQ_Element_Type(CAbstractDQ_Element_Type const& init);
	void operator=(CAbstractDQ_Element_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractDQ_Element_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_nameOfMeasure> nameOfMeasure;
	struct nameOfMeasure { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_measureIdentification> measureIdentification;
	struct measureIdentification { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_measureDescription> measureDescription;
	struct measureDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CDQ_EvaluationMethodTypeCode_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_evaluationMethodType> evaluationMethodType;
	struct evaluationMethodType { typedef Iterator<gmd::CDQ_EvaluationMethodTypeCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_evaluationMethodDescription> evaluationMethodDescription;
	struct evaluationMethodDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_evaluationProcedure> evaluationProcedure;
	struct evaluationProcedure { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_dateTime> dateTime;
	struct dateTime { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	MemberElement<gmd::CDQ_Result_PropertyType, _altova_mi_gmd_altova_CAbstractDQ_Element_Type_altova_result> result;
	struct result { typedef Iterator<gmd::CDQ_Result_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDQ_Element_Type
