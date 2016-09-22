#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CAbstractMI_GeolocationInformation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CAbstractMI_GeolocationInformation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CAbstractMI_GeolocationInformation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractMI_GeolocationInformation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractMI_GeolocationInformation_Type(CAbstractMI_GeolocationInformation_Type const& init);
	void operator=(CAbstractMI_GeolocationInformation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CAbstractMI_GeolocationInformation_Type); }
	MemberElement<gmd::CDQ_DataQuality_PropertyType, _altova_mi_gmi_altova_CAbstractMI_GeolocationInformation_Type_altova_qualityInfo> qualityInfo;
	struct qualityInfo { typedef Iterator<gmd::CDQ_DataQuality_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CAbstractMI_GeolocationInformation_Type
