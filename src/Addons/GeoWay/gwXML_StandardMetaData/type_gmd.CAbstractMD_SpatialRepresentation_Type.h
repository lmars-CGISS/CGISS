#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractMD_SpatialRepresentation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractMD_SpatialRepresentation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractMD_SpatialRepresentation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractMD_SpatialRepresentation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractMD_SpatialRepresentation_Type(CAbstractMD_SpatialRepresentation_Type const& init);
	void operator=(CAbstractMD_SpatialRepresentation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractMD_SpatialRepresentation_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractMD_SpatialRepresentation_Type
