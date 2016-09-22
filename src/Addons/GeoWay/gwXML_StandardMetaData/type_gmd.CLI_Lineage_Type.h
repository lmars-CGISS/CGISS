#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_Lineage_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_Lineage_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CLI_Lineage_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CLI_Lineage_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLI_Lineage_Type(CLI_Lineage_Type const& init);
	void operator=(CLI_Lineage_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CLI_Lineage_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CLI_Lineage_Type_altova_statement> statement;
	struct statement { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CLI_ProcessStep_PropertyType, _altova_mi_gmd_altova_CLI_Lineage_Type_altova_processStep> processStep;
	struct processStep { typedef Iterator<gmd::CLI_ProcessStep_PropertyType> iterator; };
	MemberElement<gmd::CLI_Source_PropertyType, _altova_mi_gmd_altova_CLI_Lineage_Type_altova_source> source;
	struct source { typedef Iterator<gmd::CLI_Source_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_Lineage_Type
