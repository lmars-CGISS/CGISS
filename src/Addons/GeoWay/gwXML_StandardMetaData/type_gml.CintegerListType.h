#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CintegerListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CintegerListType



namespace gie
{

namespace gml
{	

class CintegerListType : public TypeBase
{
public:
	gie_EXPORT CintegerListType(xercesc::DOMNode* const& init);
	gie_EXPORT CintegerListType(CintegerListType const& init);
	void operator=(CintegerListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CintegerListType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CintegerListType
