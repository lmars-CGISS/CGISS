#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLocalisedCharacterString_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLocalisedCharacterString_PropertyType

#include "type_gco.CObjectReference_PropertyType.h"


namespace gie
{

namespace gmd
{	

class CLocalisedCharacterString_PropertyType : public ::gie::gco::CObjectReference_PropertyType
{
public:
	gie_EXPORT CLocalisedCharacterString_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLocalisedCharacterString_PropertyType(CLocalisedCharacterString_PropertyType const& init);
	void operator=(CLocalisedCharacterString_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CLocalisedCharacterString_PropertyType); }
	MemberElement<gmd::CLocalisedCharacterString_Type, _altova_mi_gmd_altova_CLocalisedCharacterString_PropertyType_altova_LocalisedCharacterString> LocalisedCharacterString;
	struct LocalisedCharacterString { typedef Iterator<gmd::CLocalisedCharacterString_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLocalisedCharacterString_PropertyType
