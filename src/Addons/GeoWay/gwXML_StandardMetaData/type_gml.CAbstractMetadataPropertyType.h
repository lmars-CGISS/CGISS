#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMetadataPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMetadataPropertyType



namespace gie
{

namespace gml
{	

class CAbstractMetadataPropertyType : public TypeBase
{
public:
	gie_EXPORT CAbstractMetadataPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractMetadataPropertyType(CAbstractMetadataPropertyType const& init);
	void operator=(CAbstractMetadataPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractMetadataPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CAbstractMetadataPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMetadataPropertyType
