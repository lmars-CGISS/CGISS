#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CTemporalCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CTemporalCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CTemporalCSType(CTemporalCSType const& init);
	void operator=(CTemporalCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTemporalCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalCSType
