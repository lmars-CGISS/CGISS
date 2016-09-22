#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CanyURIType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CanyURIType



namespace gie
{

namespace xs
{	

class CanyURIType : public TypeBase
{
public:
	gie_EXPORT CanyURIType(xercesc::DOMNode* const& init);
	gie_EXPORT CanyURIType(CanyURIType const& init);
	void operator=(CanyURIType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CanyURIType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CanyURIType
