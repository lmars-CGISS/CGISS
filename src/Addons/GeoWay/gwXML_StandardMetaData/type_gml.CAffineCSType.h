#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAffineCSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAffineCSType

#include "type_gml.CAbstractCoordinateSystemType.h"


namespace gie
{

namespace gml
{	

class CAffineCSType : public ::gie::gml::CAbstractCoordinateSystemType
{
public:
	gie_EXPORT CAffineCSType(xercesc::DOMNode* const& init);
	gie_EXPORT CAffineCSType(CAffineCSType const& init);
	void operator=(CAffineCSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAffineCSType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAffineCSType
