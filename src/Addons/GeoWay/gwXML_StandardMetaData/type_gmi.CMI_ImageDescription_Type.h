#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_ImageDescription_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_ImageDescription_Type

#include "type_gmd.CMD_ImageDescription_Type.h"


namespace gie
{

namespace gmi
{	

class CMI_ImageDescription_Type : public ::gie::gmd::CMD_ImageDescription_Type
{
public:
	gie_EXPORT CMI_ImageDescription_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_ImageDescription_Type(CMI_ImageDescription_Type const& init);
	void operator=(CMI_ImageDescription_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_ImageDescription_Type); }
	MemberElement<gmi::CMI_RangeElementDescription_PropertyType, _altova_mi_gmi_altova_CMI_ImageDescription_Type_altova_rangeElementDescription> rangeElementDescription;
	struct rangeElementDescription { typedef Iterator<gmi::CMI_RangeElementDescription_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_ImageDescription_Type
