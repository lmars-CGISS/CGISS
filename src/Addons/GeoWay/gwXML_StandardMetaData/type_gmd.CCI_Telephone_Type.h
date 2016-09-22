#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Telephone_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Telephone_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_Telephone_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_Telephone_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_Telephone_Type(CCI_Telephone_Type const& init);
	void operator=(CCI_Telephone_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_Telephone_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Telephone_Type_altova_voice> voice;
	struct voice { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_Telephone_Type_altova_facsimile> facsimile;
	struct facsimile { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Telephone_Type
