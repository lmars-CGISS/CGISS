#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Medium_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Medium_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_Medium_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_Medium_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_Medium_Type(CMD_Medium_Type const& init);
	void operator=(CMD_Medium_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_Medium_Type); }
	MemberElement<gmd::CMD_MediumNameCode_PropertyType, _altova_mi_gmd_altova_CMD_Medium_Type_altova_name> name;
	struct name { typedef Iterator<gmd::CMD_MediumNameCode_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CMD_Medium_Type_altova_density> density;
	struct density { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Medium_Type_altova_densityUnits> densityUnits;
	struct densityUnits { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gmd_altova_CMD_Medium_Type_altova_volumes> volumes;
	struct volumes { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gmd::CMD_MediumFormatCode_PropertyType, _altova_mi_gmd_altova_CMD_Medium_Type_altova_mediumFormat> mediumFormat;
	struct mediumFormat { typedef Iterator<gmd::CMD_MediumFormatCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Medium_Type_altova_mediumNote> mediumNote;
	struct mediumNote { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Medium_Type
