#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_GCP_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_GCP_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_GCP_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMI_GCP_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_GCP_Type(CMI_GCP_Type const& init);
	void operator=(CMI_GCP_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_GCP_Type); }
	MemberElement<gmi::CDirectPosition_PropertyType, _altova_mi_gmi_altova_CMI_GCP_Type_altova_geographicCoordinates> geographicCoordinates;
	struct geographicCoordinates { typedef Iterator<gmi::CDirectPosition_PropertyType> iterator; };
	MemberElement<gmd::CDQ_Element_PropertyType, _altova_mi_gmi_altova_CMI_GCP_Type_altova_accuracyReport> accuracyReport;
	struct accuracyReport { typedef Iterator<gmd::CDQ_Element_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_GCP_Type
