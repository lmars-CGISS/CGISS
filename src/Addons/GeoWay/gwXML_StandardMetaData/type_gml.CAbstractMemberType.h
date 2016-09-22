#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMemberType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMemberType



namespace gie
{

namespace gml
{	

class CAbstractMemberType : public TypeBase
{
public:
	gie_EXPORT CAbstractMemberType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractMemberType(CAbstractMemberType const& init);
	void operator=(CAbstractMemberType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractMemberType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CAbstractMemberType_altova_owns, 0, 0> owns;	// owns Cboolean
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMemberType
