#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCalDateType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCalDateType



namespace gie
{

namespace gml
{	

class CCalDateType : public TypeBase
{
public:
	gie_EXPORT CCalDateType(xercesc::DOMNode* const& init);
	gie_EXPORT CCalDateType(CCalDateType const& init);
	void operator=(CCalDateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCalDateType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCalDateType
