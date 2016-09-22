#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Algorithm_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Algorithm_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CLE_Algorithm_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CLE_Algorithm_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_Algorithm_Type(CLE_Algorithm_Type const& init);
	void operator=(CLE_Algorithm_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_Algorithm_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmi_altova_CLE_Algorithm_Type_altova_citation> citation;
	struct citation { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CLE_Algorithm_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_Algorithm_Type
