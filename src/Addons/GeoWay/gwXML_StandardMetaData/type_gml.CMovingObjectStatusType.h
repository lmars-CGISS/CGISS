#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMovingObjectStatusType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMovingObjectStatusType

#include "type_gml.CAbstractTimeSliceType.h"


namespace gie
{

namespace gml
{	

class CMovingObjectStatusType : public ::gie::gml::CAbstractTimeSliceType
{
public:
	gie_EXPORT CMovingObjectStatusType(xercesc::DOMNode* const& init);
	gie_EXPORT CMovingObjectStatusType(CMovingObjectStatusType const& init);
	void operator=(CMovingObjectStatusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMovingObjectStatusType); }
	MemberElement<gml::CGeometryPropertyType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_position> position;
	struct position { typedef Iterator<gml::CGeometryPropertyType> iterator; };
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_locationName> locationName;
	struct locationName { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_locationReference> locationReference;
	struct locationReference { typedef Iterator<gml::CReferenceType> iterator; };
	MemberElement<gml::CLocationPropertyType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_location> location;
	struct location { typedef Iterator<gml::CLocationPropertyType> iterator; };
	MemberElement<gml::CPriorityLocationPropertyType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_priorityLocation> priorityLocation;
	struct priorityLocation { typedef Iterator<gml::CPriorityLocationPropertyType> iterator; };
	MemberElement<gml::CMeasureType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_speed> speed;
	struct speed { typedef Iterator<gml::CMeasureType> iterator; };
	MemberElement<gml::CDirectionPropertyType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_bearing> bearing;
	struct bearing { typedef Iterator<gml::CDirectionPropertyType> iterator; };
	MemberElement<gml::CMeasureType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_acceleration> acceleration;
	struct acceleration { typedef Iterator<gml::CMeasureType> iterator; };
	MemberElement<gml::CMeasureType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_elevation> elevation;
	struct elevation { typedef Iterator<gml::CMeasureType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_status> status;
	struct status { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CMovingObjectStatusType_altova_statusReference> statusReference;
	struct statusReference { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMovingObjectStatusType
