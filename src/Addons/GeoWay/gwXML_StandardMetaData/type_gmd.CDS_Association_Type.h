#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_Association_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_Association_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CDS_Association_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CDS_Association_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CDS_Association_Type(CDS_Association_Type const& init);
	void operator=(CDS_Association_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDS_Association_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_Association_Type
