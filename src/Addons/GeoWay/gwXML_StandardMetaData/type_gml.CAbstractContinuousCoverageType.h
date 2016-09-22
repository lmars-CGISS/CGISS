#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractContinuousCoverageType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractContinuousCoverageType

#include "type_gml.CAbstractCoverageType.h"


namespace gie
{

namespace gml
{	

class CAbstractContinuousCoverageType : public ::gie::gml::CAbstractCoverageType
{
public:
	gie_EXPORT CAbstractContinuousCoverageType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractContinuousCoverageType(CAbstractContinuousCoverageType const& init);
	void operator=(CAbstractContinuousCoverageType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractContinuousCoverageType); }
	MemberElement<gml::CCoverageFunctionType, _altova_mi_gml_altova_CAbstractContinuousCoverageType_altova_coverageFunction> coverageFunction;
	struct coverageFunction { typedef Iterator<gml::CCoverageFunctionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractContinuousCoverageType
