#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDynamicFeatureType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDynamicFeatureType

#include "type_gml.CAbstractFeatureType.h"


namespace gie
{

namespace gml
{	

class CDynamicFeatureType : public ::gie::gml::CAbstractFeatureType
{
public:
	gie_EXPORT CDynamicFeatureType(xercesc::DOMNode* const& init);
	gie_EXPORT CDynamicFeatureType(CDynamicFeatureType const& init);
	void operator=(CDynamicFeatureType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDynamicFeatureType); }
	MemberElement<gml::CTimePrimitivePropertyType, _altova_mi_gml_altova_CDynamicFeatureType_altova_validTime> validTime;
	struct validTime { typedef Iterator<gml::CTimePrimitivePropertyType> iterator; };
	MemberElement<gml::CHistoryPropertyType, _altova_mi_gml_altova_CDynamicFeatureType_altova_history> history;
	struct history { typedef Iterator<gml::CHistoryPropertyType> iterator; };
	MemberElement<gml::CHistoryPropertyType, _altova_mi_gml_altova_CDynamicFeatureType_altova_track> track;
	struct track { typedef Iterator<gml::CHistoryPropertyType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CDynamicFeatureType_altova_dataSource> dataSource;
	struct dataSource { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CDynamicFeatureType_altova_dataSourceReference> dataSourceReference;
	struct dataSourceReference { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDynamicFeatureType
