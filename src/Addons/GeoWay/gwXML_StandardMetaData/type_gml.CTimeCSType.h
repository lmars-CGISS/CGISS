#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CTimeCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CTimeCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeCSType(CTimeCSType const& init);
	void operator=(CTimeCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeCSType
