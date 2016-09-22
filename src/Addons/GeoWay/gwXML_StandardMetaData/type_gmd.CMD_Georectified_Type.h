#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Georectified_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Georectified_Type

#include "type_gmd.CMD_GridSpatialRepresentation_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_Georectified_Type : public ::gie::gmd::CMD_GridSpatialRepresentation_Type
{
public:
	gie_EXPORT CMD_Georectified_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_Georectified_Type(CMD_Georectified_Type const& init);
	void operator=(CMD_Georectified_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_Georectified_Type); }
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_checkPointAvailability> checkPointAvailability;
	struct checkPointAvailability { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_checkPointDescription> checkPointDescription;
	struct checkPointDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gss::CGM_Point_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_cornerPoints> cornerPoints;
	struct cornerPoints { typedef Iterator<gss::CGM_Point_PropertyType> iterator; };
	MemberElement<gss::CGM_Point_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_centerPoint> centerPoint;
	struct centerPoint { typedef Iterator<gss::CGM_Point_PropertyType> iterator; };
	MemberElement<gmd::CMD_PixelOrientationCode_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_pointInPixel> pointInPixel;
	struct pointInPixel { typedef Iterator<gmd::CMD_PixelOrientationCode_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_transformationDimensionDescription> transformationDimensionDescription;
	struct transformationDimensionDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Georectified_Type_altova_transformationDimensionMapping> transformationDimensionMapping;
	struct transformationDimensionMapping { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Georectified_Type
