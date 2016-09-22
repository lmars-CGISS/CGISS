#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CObliqueCartesianCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CObliqueCartesianCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CObliqueCartesianCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CObliqueCartesianCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CObliqueCartesianCSType(CObliqueCartesianCSType const& init);
	void operator=(CObliqueCartesianCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CObliqueCartesianCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CObliqueCartesianCSType
