#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_PlatformPass_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_PlatformPass_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_PlatformPass_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_PlatformPass_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_PlatformPass_Type(CMI_PlatformPass_Type const& init);
	void operator=(CMI_PlatformPass_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_PlatformPass_Type); }
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmi_altova_CMI_PlatformPass_Type_altova_identifier> identifier;
	struct identifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	MemberElement<gss::CGM_Object_PropertyType, _altova_mi_gmi_altova_CMI_PlatformPass_Type_altova_extent> extent;
	struct extent { typedef Iterator<gss::CGM_Object_PropertyType> iterator; };
	MemberElement<gmi::CMI_Event_PropertyType, _altova_mi_gmi_altova_CMI_PlatformPass_Type_altova_relatedEvent> relatedEvent;
	struct relatedEvent { typedef Iterator<gmi::CMI_Event_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_PlatformPass_Type
