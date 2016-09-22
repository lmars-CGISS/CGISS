#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Metadata_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Metadata_Type

#include "type_gmd.CMD_Metadata_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Metadata_Type : public ::gie::gmd::CMD_Metadata_Type
{
public:
	gie_EXPORT CMI_Metadata_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Metadata_Type(CMI_Metadata_Type const& init);
	void operator=(CMI_Metadata_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Metadata_Type); }
	MemberElement<gmi::CMI_AcquisitionInformation_PropertyType, _altova_mi_gmi_altova_CMI_Metadata_Type_altova_acquisitionInformation> acquisitionInformation;
	struct acquisitionInformation { typedef Iterator<gmi::CMI_AcquisitionInformation_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Metadata_Type
