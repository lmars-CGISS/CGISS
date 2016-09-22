#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_LegalConstraints_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_LegalConstraints_Type

#include "type_gmd.CMD_Constraints_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_LegalConstraints_Type : public ::gie::gmd::CMD_Constraints_Type
{
public:
	gie_EXPORT CMD_LegalConstraints_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_LegalConstraints_Type(CMD_LegalConstraints_Type const& init);
	void operator=(CMD_LegalConstraints_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_LegalConstraints_Type); }
	MemberElement<gmd::CMD_RestrictionCode_PropertyType, _altova_mi_gmd_altova_CMD_LegalConstraints_Type_altova_accessConstraints> accessConstraints;
	struct accessConstraints { typedef Iterator<gmd::CMD_RestrictionCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_RestrictionCode_PropertyType, _altova_mi_gmd_altova_CMD_LegalConstraints_Type_altova_useConstraints> useConstraints;
	struct useConstraints { typedef Iterator<gmd::CMD_RestrictionCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_LegalConstraints_Type_altova_otherConstraints> otherConstraints;
	struct otherConstraints { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_LegalConstraints_Type
