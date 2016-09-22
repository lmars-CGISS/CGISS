#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_FreeText_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_FreeText_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CPT_FreeText_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CPT_FreeText_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CPT_FreeText_Type(CPT_FreeText_Type const& init);
	void operator=(CPT_FreeText_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CPT_FreeText_Type); }
	MemberElement<gmd::CLocalisedCharacterString_PropertyType, _altova_mi_gmd_altova_CPT_FreeText_Type_altova_textGroup> textGroup;
	struct textGroup { typedef Iterator<gmd::CLocalisedCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_FreeText_Type
