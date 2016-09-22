#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIndirectEntryType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIndirectEntryType



namespace gie
{

namespace gml
{	

class CIndirectEntryType : public TypeBase
{
public:
	gie_EXPORT CIndirectEntryType(xercesc::DOMNode* const& init);
	gie_EXPORT CIndirectEntryType(CIndirectEntryType const& init);
	void operator=(CIndirectEntryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CIndirectEntryType); }
	MemberElement<gml::CDefinitionProxyType, _altova_mi_gml_altova_CIndirectEntryType_altova_DefinitionProxy> DefinitionProxy;
	struct DefinitionProxy { typedef Iterator<gml::CDefinitionProxyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CIndirectEntryType
