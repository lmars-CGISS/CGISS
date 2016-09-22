#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CShellPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CShellPropertyType



namespace gie
{

namespace gml
{	

class CShellPropertyType : public TypeBase
{
public:
	gie_EXPORT CShellPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CShellPropertyType(CShellPropertyType const& init);
	void operator=(CShellPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CShellPropertyType); }
	MemberElement<gml::CShellType, _altova_mi_gml_altova_CShellPropertyType_altova_Shell> Shell;
	struct Shell { typedef Iterator<gml::CShellType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CShellPropertyType
