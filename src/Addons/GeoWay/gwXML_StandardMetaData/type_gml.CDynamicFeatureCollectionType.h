#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDynamicFeatureCollectionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDynamicFeatureCollectionType

#include "type_gml.CDynamicFeatureType.h"


namespace gie
{

namespace gml
{	

class CDynamicFeatureCollectionType : public ::gie::gml::CDynamicFeatureType
{
public:
	gie_EXPORT CDynamicFeatureCollectionType(xercesc::DOMNode* const& init);
	gie_EXPORT CDynamicFeatureCollectionType(CDynamicFeatureCollectionType const& init);
	void operator=(CDynamicFeatureCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDynamicFeatureCollectionType); }
	MemberElement<gml::CDynamicFeatureMemberType, _altova_mi_gml_altova_CDynamicFeatureCollectionType_altova_dynamicMembers> dynamicMembers;
	struct dynamicMembers { typedef Iterator<gml::CDynamicFeatureMemberType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDynamicFeatureCollectionType
