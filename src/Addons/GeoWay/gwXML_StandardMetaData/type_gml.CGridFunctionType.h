#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridFunctionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridFunctionType



namespace gie
{

namespace gml
{	

class CGridFunctionType : public TypeBase
{
public:
	gie_EXPORT CGridFunctionType(xercesc::DOMNode* const& init);
	gie_EXPORT CGridFunctionType(CGridFunctionType const& init);
	void operator=(CGridFunctionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGridFunctionType); }
	MemberElement<gml::CSequenceRuleType, _altova_mi_gml_altova_CGridFunctionType_altova_sequenceRule> sequenceRule;
	struct sequenceRule { typedef Iterator<gml::CSequenceRuleType> iterator; };
	MemberElement<gml::CintegerListType, _altova_mi_gml_altova_CGridFunctionType_altova_startPoint> startPoint;
	struct startPoint { typedef Iterator<gml::CintegerListType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGridFunctionType
