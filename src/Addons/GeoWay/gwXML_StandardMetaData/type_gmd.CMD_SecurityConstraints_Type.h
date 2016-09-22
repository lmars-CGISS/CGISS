#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_SecurityConstraints_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_SecurityConstraints_Type

#include "type_gmd.CMD_Constraints_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_SecurityConstraints_Type : public ::gie::gmd::CMD_Constraints_Type
{
public:
	gie_EXPORT CMD_SecurityConstraints_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_SecurityConstraints_Type(CMD_SecurityConstraints_Type const& init);
	void operator=(CMD_SecurityConstraints_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_SecurityConstraints_Type); }
	MemberElement<gmd::CMD_ClassificationCode_PropertyType, _altova_mi_gmd_altova_CMD_SecurityConstraints_Type_altova_classification> classification;
	struct classification { typedef Iterator<gmd::CMD_ClassificationCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_SecurityConstraints_Type_altova_userNote> userNote;
	struct userNote { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_SecurityConstraints_Type_altova_classificationSystem> classificationSystem;
	struct classificationSystem { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_SecurityConstraints_Type_altova_handlingDescription> handlingDescription;
	struct handlingDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_SecurityConstraints_Type
