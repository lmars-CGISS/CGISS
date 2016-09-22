#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNameListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNameListType



namespace gie
{

namespace gml
{	

class CNameListType : public TypeBase
{
public:
	gie_EXPORT CNameListType(xercesc::DOMNode* const& init);
	gie_EXPORT CNameListType(CNameListType const& init);
	void operator=(CNameListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CNameListType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNameListType
