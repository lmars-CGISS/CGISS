#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_VectorSpatialRepresentation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_VectorSpatialRepresentation_Type

#include "type_gmd.CAbstractMD_SpatialRepresentation_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_VectorSpatialRepresentation_Type : public ::gie::gmd::CAbstractMD_SpatialRepresentation_Type
{
public:
	gie_EXPORT CMD_VectorSpatialRepresentation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_VectorSpatialRepresentation_Type(CMD_VectorSpatialRepresentation_Type const& init);
	void operator=(CMD_VectorSpatialRepresentation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_VectorSpatialRepresentation_Type); }
	MemberElement<gmd::CMD_TopologyLevelCode_PropertyType, _altova_mi_gmd_altova_CMD_VectorSpatialRepresentation_Type_altova_topologyLevel> topologyLevel;
	struct topologyLevel { typedef Iterator<gmd::CMD_TopologyLevelCode_PropertyType> iterator; };
	MemberElement<gmd::CMD_GeometricObjects_PropertyType, _altova_mi_gmd_altova_CMD_VectorSpatialRepresentation_Type_altova_geometricObjects> geometricObjects;
	struct geometricObjects { typedef Iterator<gmd::CMD_GeometricObjects_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_VectorSpatialRepresentation_Type
