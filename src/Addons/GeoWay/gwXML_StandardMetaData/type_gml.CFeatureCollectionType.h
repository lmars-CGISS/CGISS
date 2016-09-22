#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeatureCollectionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeatureCollectionType

#include "type_gml.CAbstractFeatureCollectionType.h"


namespace gie
{

namespace gml
{	

class CFeatureCollectionType : public ::gie::gml::CAbstractFeatureCollectionType
{
public:
	gie_EXPORT CFeatureCollectionType(xercesc::DOMNode* const& init);
	gie_EXPORT CFeatureCollectionType(CFeatureCollectionType const& init);
	void operator=(CFeatureCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFeatureCollectionType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFeatureCollectionType
