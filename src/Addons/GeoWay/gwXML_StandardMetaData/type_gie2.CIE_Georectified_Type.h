#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Georectified_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Georectified_Type

#include "type_gmd.CMD_Georectified_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_Georectified_Type : public ::gie::gmd::CMD_Georectified_Type
{
public:
	gie_EXPORT CIE_Georectified_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_Georectified_Type(CIE_Georectified_Type const& init);
	void operator=(CIE_Georectified_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_Georectified_Type); }
	MemberElement<gie2::CIE_GeolocationSourceCode_PropertyType, _altova_mi_gie2_altova_CIE_Georectified_Type_altova_geolocationSource> geolocationSource;
	struct geolocationSource { typedef Iterator<gie2::CIE_GeolocationSourceCode_PropertyType> iterator; };
	MemberElement<gie2::CIE_GeometricCorrectionModelCode_PropertyType, _altova_mi_gie2_altova_CIE_Georectified_Type_altova_correctionModel> correctionModel;
	struct correctionModel { typedef Iterator<gie2::CIE_GeometricCorrectionModelCode_PropertyType> iterator; };
	MemberElement<gie2::CIE_LocationGCP_PropertyType, _altova_mi_gie2_altova_CIE_Georectified_Type_altova_checkPoints> checkPoints;
	struct checkPoints { typedef Iterator<gie2::CIE_LocationGCP_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Georectified_Type
