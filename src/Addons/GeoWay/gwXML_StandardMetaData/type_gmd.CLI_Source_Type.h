#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_Source_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_Source_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CLI_Source_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CLI_Source_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLI_Source_Type(CLI_Source_Type const& init);
	void operator=(CLI_Source_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CLI_Source_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CLI_Source_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_RepresentativeFraction_PropertyType, _altova_mi_gmd_altova_CLI_Source_Type_altova_scaleDenominator> scaleDenominator;
	struct scaleDenominator { typedef Iterator<gmd::CMD_RepresentativeFraction_PropertyType> iterator; };
	MemberElement<gmd::CMD_ReferenceSystem_PropertyType, _altova_mi_gmd_altova_CLI_Source_Type_altova_sourceReferenceSystem> sourceReferenceSystem;
	struct sourceReferenceSystem { typedef Iterator<gmd::CMD_ReferenceSystem_PropertyType> iterator; };
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmd_altova_CLI_Source_Type_altova_sourceCitation> sourceCitation;
	struct sourceCitation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gmd::CEX_Extent_PropertyType, _altova_mi_gmd_altova_CLI_Source_Type_altova_sourceExtent> sourceExtent;
	struct sourceExtent { typedef Iterator<gmd::CEX_Extent_PropertyType> iterator; };
	MemberElement<gmd::CLI_ProcessStep_PropertyType, _altova_mi_gmd_altova_CLI_Source_Type_altova_sourceStep> sourceStep;
	struct sourceStep { typedef Iterator<gmd::CLI_ProcessStep_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLI_Source_Type
