#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Format_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Format_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_Format_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_Format_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_Format_Type(CMD_Format_Type const& init);
	void operator=(CMD_Format_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_Format_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Format_Type_altova_name> name;
	struct name { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Format_Type_altova_version> version;
	struct version { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Format_Type_altova_amendmentNumber> amendmentNumber;
	struct amendmentNumber { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Format_Type_altova_specification> specification;
	struct specification { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Format_Type_altova_fileDecompressionTechnique> fileDecompressionTechnique;
	struct fileDecompressionTechnique { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CMD_Distributor_PropertyType, _altova_mi_gmd_altova_CMD_Format_Type_altova_formatDistributor> formatDistributor;
	struct formatDistributor { typedef Iterator<gmd::CMD_Distributor_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Format_Type
