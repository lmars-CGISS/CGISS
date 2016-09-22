#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Citation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Citation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_Citation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_Citation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_Citation_Type(CCI_Citation_Type const& init);
	void operator=(CCI_Citation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_Citation_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_title> title;
	struct title { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_alternateTitle> alternateTitle;
	struct alternateTitle { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_Date_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_date> date;
	struct date { typedef Iterator<gmd::CCI_Date_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_edition> edition;
	struct edition { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CDate_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_editionDate> editionDate;
	struct editionDate { typedef Iterator<gco::CDate_PropertyType> iterator; };
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_citedResponsibleParty> citedResponsibleParty;
	struct citedResponsibleParty { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gmd::CCI_PresentationFormCode_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_presentationForm> presentationForm;
	struct presentationForm { typedef Iterator<gmd::CCI_PresentationFormCode_PropertyType> iterator; };
	MemberElement<gmd::CCI_Series_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_series> series;
	struct series { typedef Iterator<gmd::CCI_Series_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_otherCitationDetails> otherCitationDetails;
	struct otherCitationDetails { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_collectiveTitle> collectiveTitle;
	struct collectiveTitle { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_ISBN> ISBN;
	struct ISBN { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Citation_Type_altova_ISSN> ISSN;
	struct ISSN { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Citation_Type
