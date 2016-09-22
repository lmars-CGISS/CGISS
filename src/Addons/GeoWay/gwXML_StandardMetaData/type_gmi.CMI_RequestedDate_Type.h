#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RequestedDate_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RequestedDate_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_RequestedDate_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_RequestedDate_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_RequestedDate_Type(CMI_RequestedDate_Type const& init);
	void operator=(CMI_RequestedDate_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_RequestedDate_Type); }
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gmi_altova_CMI_RequestedDate_Type_altova_requestedDateOfCollection> requestedDateOfCollection;
	struct requestedDateOfCollection { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gmi_altova_CMI_RequestedDate_Type_altova_latestAcceptableDate> latestAcceptableDate;
	struct latestAcceptableDate { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_RequestedDate_Type
