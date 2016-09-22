#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_ConformanceResult_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_ConformanceResult_Type

#include "type_gmd.CAbstractDQ_Result_Type.h"


namespace gie
{

namespace gmd
{	

class CDQ_ConformanceResult_Type : public ::gie::gmd::CAbstractDQ_Result_Type
{
public:
	gie_EXPORT CDQ_ConformanceResult_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CDQ_ConformanceResult_Type(CDQ_ConformanceResult_Type const& init);
	void operator=(CDQ_ConformanceResult_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDQ_ConformanceResult_Type); }
	MemberElement<gmd::CCI_Citation_PropertyType, _altova_mi_gmd_altova_CDQ_ConformanceResult_Type_altova_specification> specification;
	struct specification { typedef Iterator<gmd::CCI_Citation_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CDQ_ConformanceResult_Type_altova_explanation> explanation;
	struct explanation { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CBoolean_PropertyType, _altova_mi_gmd_altova_CDQ_ConformanceResult_Type_altova_pass> pass;
	struct pass { typedef Iterator<gco::CBoolean_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDQ_ConformanceResult_Type
