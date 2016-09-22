#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ApplicationSchemaInformation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ApplicationSchemaInformation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_ApplicationSchemaInformation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_ApplicationSchemaInformation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_ApplicationSchemaInformation_Type(CMD_ApplicationSchemaInformation_Type const& init);
	void operator=(CMD_ApplicationSchemaInformation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_ApplicationSchemaInformation_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_name> name;
	struct name { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_schemaLanguage> schemaLanguage;
	struct schemaLanguage { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_constraintLanguage> constraintLanguage;
	struct constraintLanguage { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_schemaAscii> schemaAscii;
	struct schemaAscii { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CBinary_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_graphicsFile> graphicsFile;
	struct graphicsFile { typedef Iterator<gco::CBinary_PropertyType> iterator; };
	MemberElement<gco::CBinary_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_softwareDevelopmentFile> softwareDevelopmentFile;
	struct softwareDevelopmentFile { typedef Iterator<gco::CBinary_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_ApplicationSchemaInformation_Type_altova_softwareDevelopmentFileFormat> softwareDevelopmentFileFormat;
	struct softwareDevelopmentFileFormat { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ApplicationSchemaInformation_Type
