#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CQE_CoverageResult_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CQE_CoverageResult_Type

#include "type_gmd.CAbstractDQ_Result_Type.h"


namespace gie
{

namespace gmi
{	

class CQE_CoverageResult_Type : public ::gie::gmd::CAbstractDQ_Result_Type
{
public:
	gie_EXPORT CQE_CoverageResult_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CQE_CoverageResult_Type(CQE_CoverageResult_Type const& init);
	void operator=(CQE_CoverageResult_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CQE_CoverageResult_Type); }
	MemberElement<gmd::CMD_SpatialRepresentationTypeCode_PropertyType, _altova_mi_gmi_altova_CQE_CoverageResult_Type_altova_spatialRepresentationType> spatialRepresentationType;
	struct spatialRepresentationType { typedef Iterator<gmd::CMD_SpatialRepresentationTypeCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_SpatialRepresentation_PropertyType, _altova_mi_gmi_altova_CQE_CoverageResult_Type_altova_resultSpatialRepresentation> resultSpatialRepresentation;
	struct resultSpatialRepresentation { typedef Iterator<gmd::CMD_SpatialRepresentation_PropertyType> iterator; };
	MemberElement<gmd::CMD_CoverageDescription_PropertyType, _altova_mi_gmi_altova_CQE_CoverageResult_Type_altova_resultContentDescription> resultContentDescription;
	struct resultContentDescription { typedef Iterator<gmd::CMD_CoverageDescription_PropertyType> iterator; };
	MemberElement<gmd::CMD_Format_PropertyType, _altova_mi_gmi_altova_CQE_CoverageResult_Type_altova_resultFormat> resultFormat;
	struct resultFormat { typedef Iterator<gmd::CMD_Format_PropertyType> iterator; };
	MemberElement<gmi::CMX_DataFile_PropertyType, _altova_mi_gmi_altova_CQE_CoverageResult_Type_altova_resultFile> resultFile;
	struct resultFile { typedef Iterator<gmi::CMX_DataFile_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CQE_CoverageResult_Type
