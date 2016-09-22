#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrowsType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrowsType



namespace gie
{

namespace gml
{	

class CrowsType : public TypeBase
{
public:
	gie_EXPORT CrowsType(xercesc::DOMNode* const& init);
	gie_EXPORT CrowsType(CrowsType const& init);
	void operator=(CrowsType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CrowsType); }
	MemberElement<gml::CRowType, _altova_mi_gml_altova_CrowsType_altova_Row> Row;
	struct Row { typedef Iterator<gml::CRowType> iterator; };
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrowsType
