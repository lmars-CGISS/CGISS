#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractDiscreteCoverageType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractDiscreteCoverageType

#include "type_gml.CAbstractCoverageType.h"


namespace gie
{

namespace gml
{	

class CAbstractDiscreteCoverageType : public ::gie::gml::CAbstractCoverageType
{
public:
	gie_EXPORT CAbstractDiscreteCoverageType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractDiscreteCoverageType(CAbstractDiscreteCoverageType const& init);
	void operator=(CAbstractDiscreteCoverageType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractDiscreteCoverageType); }
	MemberElement<gml::CCoverageFunctionType, _altova_mi_gml_altova_CAbstractDiscreteCoverageType_altova_coverageFunction> coverageFunction;
	struct coverageFunction { typedef Iterator<gml::CCoverageFunctionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractDiscreteCoverageType
