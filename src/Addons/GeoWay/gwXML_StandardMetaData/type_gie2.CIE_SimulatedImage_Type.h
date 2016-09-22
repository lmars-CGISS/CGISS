#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SimulatedImage_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SimulatedImage_Type

#include "type_gie2.CIE_SyntheticImage_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_SimulatedImage_Type : public ::gie::gie2::CIE_SyntheticImage_Type
{
public:
	gie_EXPORT CIE_SimulatedImage_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SimulatedImage_Type(CIE_SimulatedImage_Type const& init);
	void operator=(CIE_SimulatedImage_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SimulatedImage_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_SimulatedImage_Type_altova_simulateMethod> simulateMethod;
	struct simulateMethod { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CLI_Lineage_PropertyType, _altova_mi_gie2_altova_CIE_SimulatedImage_Type_altova_provenance> provenance;
	struct provenance { typedef Iterator<gmd::CLI_Lineage_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SimulatedImage_Type
