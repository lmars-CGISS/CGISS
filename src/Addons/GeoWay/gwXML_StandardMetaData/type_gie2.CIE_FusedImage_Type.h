#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_FusedImage_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_FusedImage_Type

#include "type_gie2.CIE_SyntheticImage_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_FusedImage_Type : public ::gie::gie2::CIE_SyntheticImage_Type
{
public:
	gie_EXPORT CIE_FusedImage_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_FusedImage_Type(CIE_FusedImage_Type const& init);
	void operator=(CIE_FusedImage_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_FusedImage_Type); }
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_FusedImage_Type_altova_numberOfSourceImages> numberOfSourceImages;
	struct numberOfSourceImages { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gmi::CLE_ProcessStep_PropertyType, _altova_mi_gie2_altova_CIE_FusedImage_Type_altova_processingSteps> processingSteps;
	struct processingSteps { typedef Iterator<gmi::CLE_ProcessStep_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_FusedImage_Type
