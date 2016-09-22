#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVolumeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVolumeType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gml
{	

class CVolumeType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CVolumeType(xercesc::DOMNode* const& init);
	gie_EXPORT CVolumeType(CVolumeType const& init);
	void operator=(CVolumeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CVolumeType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CVolumeType
