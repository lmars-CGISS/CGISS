#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWChannelInfo_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWChannelInfo_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_PMWChannelInfo_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_PMWChannelInfo_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_PMWChannelInfo_Type(CIE_PMWChannelInfo_Type const& init);
	void operator=(CIE_PMWChannelInfo_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_PMWChannelInfo_Type); }
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_PMWChannelInfo_Type_altova_channelWidth> channelWidth;
	struct channelWidth { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_PMWChannelInfo_Type_altova_centreFrequency> centreFrequency;
	struct centreFrequency { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gie2::CIE_ChannelPropertyCode_PropertyType, _altova_mi_gie2_altova_CIE_PMWChannelInfo_Type_altova_channelProperty> channelProperty;
	struct channelProperty { typedef Iterator<gie2::CIE_ChannelPropertyCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_PMWChannelInfo_Type
