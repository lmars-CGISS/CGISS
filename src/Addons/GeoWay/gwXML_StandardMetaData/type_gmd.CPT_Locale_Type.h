#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_Locale_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_Locale_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CPT_Locale_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CPT_Locale_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CPT_Locale_Type(CPT_Locale_Type const& init);
	void operator=(CPT_Locale_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CPT_Locale_Type); }
	MemberElement<gmd::CLanguageCode_PropertyType, _altova_mi_gmd_altova_CPT_Locale_Type_altova_languageCode> languageCode;
	struct languageCode { typedef Iterator<gmd::CLanguageCode_PropertyType> iterator; };
	MemberElement<gmd::CCountry_PropertyType, _altova_mi_gmd_altova_CPT_Locale_Type_altova_country> country;
	struct country { typedef Iterator<gmd::CCountry_PropertyType> iterator; };
	MemberElement<gmd::CMD_CharacterSetCode_PropertyType, _altova_mi_gmd_altova_CPT_Locale_Type_altova_characterEncoding> characterEncoding;
	struct characterEncoding { typedef Iterator<gmd::CMD_CharacterSetCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_Locale_Type
