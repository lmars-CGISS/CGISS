#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMetaDataType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMetaDataType



namespace gie
{

namespace gml
{	

class CAbstractMetaDataType : public TypeBase
{
public:
	gie_EXPORT CAbstractMetaDataType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractMetaDataType(CAbstractMetaDataType const& init);
	void operator=(CAbstractMetaDataType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractMetaDataType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractMetaDataType_altova_id, 0, 0> id;	// id CID
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractMetaDataType
