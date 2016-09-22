#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_ProcessStepReport_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_ProcessStepReport_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CLE_ProcessStepReport_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CLE_ProcessStepReport_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_ProcessStepReport_Type(CLE_ProcessStepReport_Type const& init);
	void operator=(CLE_ProcessStepReport_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_ProcessStepReport_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CLE_ProcessStepReport_Type_altova_name> name;
	struct name { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CLE_ProcessStepReport_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmi_altova_CLE_ProcessStepReport_Type_altova_fileType> fileType;
	struct fileType { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_ProcessStepReport_Type
