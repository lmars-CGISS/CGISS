#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrefLocationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrefLocationType



namespace gie
{

namespace gml
{	

class CrefLocationType : public TypeBase
{
public:
	gie_EXPORT CrefLocationType(xercesc::DOMNode* const& init);
	gie_EXPORT CrefLocationType(CrefLocationType const& init);
	void operator=(CrefLocationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CrefLocationType); }
	MemberElement<gml::CAffinePlacementType, _altova_mi_gml_altova_CrefLocationType_altova_AffinePlacement> AffinePlacement;
	struct AffinePlacement { typedef Iterator<gml::CAffinePlacementType> iterator; };
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrefLocationType
