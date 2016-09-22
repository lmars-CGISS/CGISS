#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEngineeringDatumType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEngineeringDatumType

#include "type_gml.CAbstractDatumType.h"


namespace gie
{

namespace gml
{	

class CEngineeringDatumType : public ::gie::gml::CAbstractDatumType
{
public:
	gie_EXPORT CEngineeringDatumType(xercesc::DOMNode* const& init);
	gie_EXPORT CEngineeringDatumType(CEngineeringDatumType const& init);
	void operator=(CEngineeringDatumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CEngineeringDatumType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEngineeringDatumType
