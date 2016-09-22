#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CstringType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CstringType



namespace gie
{

namespace xs
{	

class CstringType : public TypeBase
{
public:
	gie_EXPORT CstringType(xercesc::DOMNode* const& init);
	gie_EXPORT CstringType(CstringType const& init);
	void operator=(CstringType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CstringType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CstringType
