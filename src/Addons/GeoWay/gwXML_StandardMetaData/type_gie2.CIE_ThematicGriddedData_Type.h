#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ThematicGriddedData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ThematicGriddedData_Type

#include "type_gie2.CAbstractIE_ImageryandGriddedData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_ThematicGriddedData_Type : public ::gie::gie2::CAbstractIE_ImageryandGriddedData_Type
{
public:
	gie_EXPORT CIE_ThematicGriddedData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_ThematicGriddedData_Type(CIE_ThematicGriddedData_Type const& init);
	void operator=(CIE_ThematicGriddedData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_ThematicGriddedData_Type); }
	MemberElement<gmd::CMD_CoverageDescription_PropertyType, _altova_mi_gie2_altova_CIE_ThematicGriddedData_Type_altova_dataInfo> dataInfo;
	struct dataInfo { typedef Iterator<gmd::CMD_CoverageDescription_PropertyType> iterator; };
	MemberElement<gss::CGM_Object_PropertyType, _altova_mi_gie2_altova_CIE_ThematicGriddedData_Type_altova_annotation> annotation;
	struct annotation { typedef Iterator<gss::CGM_Object_PropertyType> iterator; };
	MemberElement<gss::CGM_Object_PropertyType, _altova_mi_gie2_altova_CIE_ThematicGriddedData_Type_altova_geographicFeature> geographicFeature;
	struct geographicFeature { typedef Iterator<gss::CGM_Object_PropertyType> iterator; };
	MemberElement<gmi::CLE_Processing_PropertyType, _altova_mi_gie2_altova_CIE_ThematicGriddedData_Type_altova_retrievalProcessingInfo> retrievalProcessingInfo;
	struct retrievalProcessingInfo { typedef Iterator<gmi::CLE_Processing_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_ThematicGriddedData_Type_altova_sourceInfo> sourceInfo;
	struct sourceInfo { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ThematicGriddedData_Type
