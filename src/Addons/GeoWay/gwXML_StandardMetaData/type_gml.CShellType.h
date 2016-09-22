#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CShellType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CShellType



namespace gie
{

namespace gml
{	

class CShellType : public TypeBase
{
public:
	gie_EXPORT CShellType(xercesc::DOMNode* const& init);
	gie_EXPORT CShellType(CShellType const& init);
	void operator=(CShellType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CShellType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CShellType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CSurfacePropertyType, _altova_mi_gml_altova_CShellType_altova_surfaceMember> surfaceMember;
	struct surfaceMember { typedef Iterator<gml::CSurfacePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CShellType
