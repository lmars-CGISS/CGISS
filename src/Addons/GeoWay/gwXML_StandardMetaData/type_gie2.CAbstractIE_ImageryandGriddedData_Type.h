#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_ImageryandGriddedData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_ImageryandGriddedData_Type

#include "type_gcv.CCV_Coverage_Type.h"


namespace gie
{

namespace gie2
{	

class CAbstractIE_ImageryandGriddedData_Type : public ::gie::gcv::CCV_Coverage_Type
{
public:
	gie_EXPORT CAbstractIE_ImageryandGriddedData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractIE_ImageryandGriddedData_Type(CAbstractIE_ImageryandGriddedData_Type const& init);
	void operator=(CAbstractIE_ImageryandGriddedData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CAbstractIE_ImageryandGriddedData_Type); }
	MemberElement<gcv::CCV_InterpolationMethod_PropertyType, _altova_mi_gie2_altova_CAbstractIE_ImageryandGriddedData_Type_altova_interpolationType> interpolationType;
	struct interpolationType { typedef Iterator<gcv::CCV_InterpolationMethod_PropertyType> iterator; };
	MemberElement<gie2::CIE_Georectified_PropertyType, _altova_mi_gie2_altova_CAbstractIE_ImageryandGriddedData_Type_altova_georectifedSpatialInfo> georectifedSpatialInfo;
	struct georectifedSpatialInfo { typedef Iterator<gie2::CIE_Georectified_PropertyType> iterator; };
	MemberElement<gie2::CIE_Georeferenceable_PropertyType, _altova_mi_gie2_altova_CAbstractIE_ImageryandGriddedData_Type_altova_georeferenceableSpatialInfo> georeferenceableSpatialInfo;
	struct georeferenceableSpatialInfo { typedef Iterator<gie2::CIE_Georeferenceable_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CAbstractIE_ImageryandGriddedData_Type
