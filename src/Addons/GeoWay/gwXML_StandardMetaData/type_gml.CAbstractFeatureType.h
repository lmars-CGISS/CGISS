#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CAbstractFeatureType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CAbstractFeatureType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractFeatureType(CAbstractFeatureType const& init);
	void operator=(CAbstractFeatureType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractFeatureType); }
	MemberElement<gml::CBoundingShapeType, _altova_mi_gml_altova_CAbstractFeatureType_altova_boundedBy> boundedBy;
	struct boundedBy { typedef Iterator<gml::CBoundingShapeType> iterator; };
	MemberElement<gml::CLocationPropertyType, _altova_mi_gml_altova_CAbstractFeatureType_altova_location> location;
	struct location { typedef Iterator<gml::CLocationPropertyType> iterator; };
	MemberElement<gml::CPriorityLocationPropertyType, _altova_mi_gml_altova_CAbstractFeatureType_altova_priorityLocation> priorityLocation;
	struct priorityLocation { typedef Iterator<gml::CPriorityLocationPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureType
