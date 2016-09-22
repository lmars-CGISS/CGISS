#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureMemberType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureMemberType



namespace gie
{

namespace gml
{	

class CAbstractFeatureMemberType : public TypeBase
{
public:
	gie_EXPORT CAbstractFeatureMemberType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractFeatureMemberType(CAbstractFeatureMemberType const& init);
	void operator=(CAbstractFeatureMemberType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractFeatureMemberType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CAbstractFeatureMemberType_altova_owns, 0, 0> owns;	// owns Cboolean
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractFeatureMemberType
