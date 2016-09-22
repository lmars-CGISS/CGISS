#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLocalisedCharacterString_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLocalisedCharacterString_Type

#include "type_xs.CstringType.h"


namespace gie
{

namespace gmd
{	

class CLocalisedCharacterString_Type : public ::gie::xs::CstringType
{
public:
	gie_EXPORT CLocalisedCharacterString_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLocalisedCharacterString_Type(CLocalisedCharacterString_Type const& init);
	void operator=(CLocalisedCharacterString_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CLocalisedCharacterString_Type); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLocalisedCharacterString_Type_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_gmd_altova_CLocalisedCharacterString_Type_altova_locale, 0, 0> locale;	// locale CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLocalisedCharacterString_Type
