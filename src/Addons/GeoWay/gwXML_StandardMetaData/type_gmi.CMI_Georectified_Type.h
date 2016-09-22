#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Georectified_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Georectified_Type

#include "type_gmd.CMD_Georectified_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Georectified_Type : public ::gie::gmd::CMD_Georectified_Type
{
public:
	gie_EXPORT CMI_Georectified_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Georectified_Type(CMI_Georectified_Type const& init);
	void operator=(CMI_Georectified_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Georectified_Type); }
	MemberElement<gmi::CMI_GCP_PropertyType, _altova_mi_gmi_altova_CMI_Georectified_Type_altova_checkPoint> checkPoint;
	struct checkPoint { typedef Iterator<gmi::CMI_GCP_PropertyType> iterator; };
	MemberElement<gmi::CMI_GCPCollection_PropertyType, _altova_mi_gmi_altova_CMI_Georectified_Type_altova_geolocationIdentification> geolocationIdentification;
	struct geolocationIdentification { typedef Iterator<gmi::CMI_GCPCollection_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Georectified_Type
