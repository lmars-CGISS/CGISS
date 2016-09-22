#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeWithAuthorityType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeWithAuthorityType



namespace gie
{

namespace gml
{	

class CCodeWithAuthorityType : public TypeBase
{
public:
	gie_EXPORT CCodeWithAuthorityType(xercesc::DOMNode* const& init);
	gie_EXPORT CCodeWithAuthorityType(CCodeWithAuthorityType const& init);
	void operator=(CCodeWithAuthorityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCodeWithAuthorityType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_gml_altova_CCodeWithAuthorityType_altova_codeSpace, 0, 0> codeSpace;	// codeSpace CanyURI
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCodeWithAuthorityType
