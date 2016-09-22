#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMappingRuleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMappingRuleType



namespace gie
{

namespace gml
{	

class CMappingRuleType : public TypeBase
{
public:
	gie_EXPORT CMappingRuleType(xercesc::DOMNode* const& init);
	gie_EXPORT CMappingRuleType(CMappingRuleType const& init);
	void operator=(CMappingRuleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMappingRuleType); }
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CMappingRuleType_altova_ruleDefinition> ruleDefinition;
	struct ruleDefinition { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CMappingRuleType_altova_ruleReference> ruleReference;
	struct ruleReference { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMappingRuleType
