#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Source_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Source_Type

#include "type_gmd.CLI_Source_Type.h"


namespace gie
{

namespace gmi
{	

class CLE_Source_Type : public ::gie::gmd::CLI_Source_Type
{
public:
	gie_EXPORT CLE_Source_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_Source_Type(CLE_Source_Type const& init);
	void operator=(CLE_Source_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_Source_Type); }
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CLE_Source_Type_altova_processedLevel> processedLevel;
	struct processedLevel { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gmi::CLE_NominalResolution_PropertyType, _altova_mi_gmi_altova_CLE_Source_Type_altova_resolution> resolution;
	struct resolution { typedef Iterator<gmi::CLE_NominalResolution_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Source_Type
