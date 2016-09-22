#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureCollectionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureCollectionType

#include "type_gml.CAbstractFeatureType.h"


namespace gie
{

namespace gml
{	

class CAbstractFeatureCollectionType : public ::gie::gml::CAbstractFeatureType
{
public:
	gie_EXPORT CAbstractFeatureCollectionType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractFeatureCollectionType(CAbstractFeatureCollectionType const& init);
	void operator=(CAbstractFeatureCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractFeatureCollectionType); }
	MemberElement<gml::CFeaturePropertyType, _altova_mi_gml_altova_CAbstractFeatureCollectionType_altova_featureMember> featureMember;
	struct featureMember { typedef Iterator<gml::CFeaturePropertyType> iterator; };
	MemberElement<gml::CFeatureArrayPropertyType, _altova_mi_gml_altova_CAbstractFeatureCollectionType_altova_featureMembers> featureMembers;
	struct featureMembers { typedef Iterator<gml::CFeatureArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureCollectionType
