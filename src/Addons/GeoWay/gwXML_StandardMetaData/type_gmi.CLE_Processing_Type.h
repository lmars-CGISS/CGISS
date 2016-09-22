#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Processing_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Processing_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CLE_Processing_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CLE_Processing_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_Processing_Type(CLE_Processing_Type const& init);
	void operator=(CLE_Processing_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_Processing_Type); }
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CLE_Processing_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CLE_Processing_Type_altova_softwareReference> softwareReference;
	struct softwareReference { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CLE_Processing_Type_altova_procedureDescription> procedureDescription;
	struct procedureDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CLE_Processing_Type_altova_documentation> documentation;
	struct documentation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CLE_Processing_Type_altova_runTimeParameters> runTimeParameters;
	struct runTimeParameters { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmi::CLE_Algorithm_PropertyType, _altova_mi_gmi_altova_CLE_Processing_Type_altova_algorithm> algorithm;
	struct algorithm { typedef Iterator<gmi::CLE_Algorithm_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Processing_Type
