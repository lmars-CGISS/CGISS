#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_CoverageDescription_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_CoverageDescription_Type

#include "type_gmd.CMD_CoverageDescription_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_CoverageDescription_Type : public ::gie::gmd::CMD_CoverageDescription_Type
{
public:
	gie_EXPORT CMI_CoverageDescription_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_CoverageDescription_Type(CMI_CoverageDescription_Type const& init);
	void operator=(CMI_CoverageDescription_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_CoverageDescription_Type); }
	MemberElement<gmi::CMI_RangeElementDescription_PropertyType, _altova_mi_gmi_altova_CMI_CoverageDescription_Type_altova_rangeElementDescription> rangeElementDescription;
	struct rangeElementDescription { typedef Iterator<gmi::CMI_RangeElementDescription_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_CoverageDescription_Type
