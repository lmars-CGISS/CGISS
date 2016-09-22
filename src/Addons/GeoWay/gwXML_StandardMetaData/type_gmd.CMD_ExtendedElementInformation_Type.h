#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ExtendedElementInformation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ExtendedElementInformation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_ExtendedElementInformation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_ExtendedElementInformation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_ExtendedElementInformation_Type(CMD_ExtendedElementInformation_Type const& init);
	void operator=(CMD_ExtendedElementInformation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_ExtendedElementInformation_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_name> name;
	struct name { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_shortName> shortName;
	struct shortName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_domainCode> domainCode;
	struct domainCode { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_definition> definition;
	struct definition { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_ObligationCode_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_obligation> obligation;
	struct obligation { typedef Iterator<gmd::CMD_ObligationCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_condition> condition;
	struct condition { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_DatatypeCode_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_dataType> dataType;
	struct dataType { typedef Iterator<gmd::CMD_DatatypeCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_maximumOccurrence> maximumOccurrence;
	struct maximumOccurrence { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_domainValue> domainValue;
	struct domainValue { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_parentEntity> parentEntity;
	struct parentEntity { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_rule> rule;
	struct rule { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_rationale> rationale;
	struct rationale { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmd_altova_CMD_ExtendedElementInformation_Type_altova_source> source;
	struct source { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ExtendedElementInformation_Type
