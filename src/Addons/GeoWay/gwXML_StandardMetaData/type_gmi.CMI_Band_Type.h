#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Band_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Band_Type

#include "type_gmd.CMD_Band_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_Band_Type : public ::gie::gmd::CMD_Band_Type
{
public:
	gie_EXPORT CMI_Band_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_Band_Type(CMI_Band_Type const& init);
	void operator=(CMI_Band_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_Band_Type); }
	MemberElement<gmi::CMI_BandDefinition_PropertyType, _altova_mi_gmi_altova_CMI_Band_Type_altova_bandBoundaryDefinition> bandBoundaryDefinition;
	struct bandBoundaryDefinition { typedef Iterator<gmi::CMI_BandDefinition_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmi_altova_CMI_Band_Type_altova_nominalSpatialResolution> nominalSpatialResolution;
	struct nominalSpatialResolution { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gmi::CMI_TransferFunctionTypeCode_PropertyType, _altova_mi_gmi_altova_CMI_Band_Type_altova_transferFunctionType> transferFunctionType;
	struct transferFunctionType { typedef Iterator<gmi::CMI_TransferFunctionTypeCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_PolarisationOrientationCode_PropertyType, _altova_mi_gmi_altova_CMI_Band_Type_altova_transmittedPolarisation> transmittedPolarisation;
	struct transmittedPolarisation { typedef Iterator<gmi::CMI_PolarisationOrientationCode_PropertyType> iterator; };
	MemberElement<gmi::CMI_PolarisationOrientationCode_PropertyType, _altova_mi_gmi_altova_CMI_Band_Type_altova_detectedPolarisation> detectedPolarisation;
	struct detectedPolarisation { typedef Iterator<gmi::CMI_PolarisationOrientationCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_Band_Type
