#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWBand_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWBand_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_PMWBand_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_PMWBand_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_PMWBand_Type(CIE_PMWBand_Type const& init);
	void operator=(CIE_PMWBand_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_PMWBand_Type); }
	MemberElement<gie2::CIE_PMWBandNameCode_PropertyType, _altova_mi_gie2_altova_CIE_PMWBand_Type_altova_bandName> bandName;
	struct bandName { typedef Iterator<gie2::CIE_PMWBandNameCode_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_PMWBand_Type_altova_numberOfChannels> numberOfChannels;
	struct numberOfChannels { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gie2::CIE_PMWChannelInfo_PropertyType, _altova_mi_gie2_altova_CIE_PMWBand_Type_altova_channels> channels;
	struct channels { typedef Iterator<gie2::CIE_PMWChannelInfo_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWBand_Type
