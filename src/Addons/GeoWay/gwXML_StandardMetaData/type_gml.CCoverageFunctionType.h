#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoverageFunctionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoverageFunctionType



namespace gie
{

namespace gml
{	

class CCoverageFunctionType : public TypeBase
{
public:
	gie_EXPORT CCoverageFunctionType(xercesc::DOMNode* const& init);
	gie_EXPORT CCoverageFunctionType(CCoverageFunctionType const& init);
	void operator=(CCoverageFunctionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCoverageFunctionType); }
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CCoverageFunctionType_altova_MappingRule> MappingRule;
	struct MappingRule { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CMappingRuleType, _altova_mi_gml_altova_CCoverageFunctionType_altova_CoverageMappingRule> CoverageMappingRule;
	struct CoverageMappingRule { typedef Iterator<gml::CMappingRuleType> iterator; };
	MemberElement<gml::CGridFunctionType, _altova_mi_gml_altova_CCoverageFunctionType_altova_GridFunction> GridFunction;
	struct GridFunction { typedef Iterator<gml::CGridFunctionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoverageFunctionType
