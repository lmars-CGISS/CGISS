#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CQE_Usability_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CQE_Usability_Type

#include "type_gmd.CAbstractDQ_Element_Type.h"


namespace gie
{

namespace gmi
{	

class CQE_Usability_Type : public ::gie::gmd::CAbstractDQ_Element_Type
{
public:
	gie_EXPORT CQE_Usability_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CQE_Usability_Type(CQE_Usability_Type const& init);
	void operator=(CQE_Usability_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CQE_Usability_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CQE_Usability_Type
