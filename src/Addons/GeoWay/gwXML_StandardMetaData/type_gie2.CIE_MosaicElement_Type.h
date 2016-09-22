#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_MosaicElement_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_MosaicElement_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_MosaicElement_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_MosaicElement_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_MosaicElement_Type(CIE_MosaicElement_Type const& init);
	void operator=(CIE_MosaicElement_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_MosaicElement_Type); }
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_MosaicElement_Type_altova_elementID> elementID;
	struct elementID { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gcv::CTM_Period_PropertyType, _altova_mi_gie2_altova_CIE_MosaicElement_Type_altova_acquisitionTime> acquisitionTime;
	struct acquisitionTime { typedef Iterator<gcv::CTM_Period_PropertyType> iterator; };
	MemberElement<gmd::CEX_Extent_PropertyType, _altova_mi_gie2_altova_CIE_MosaicElement_Type_altova_geometry> geometry;
	struct geometry { typedef Iterator<gmd::CEX_Extent_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_MosaicElement_Type
