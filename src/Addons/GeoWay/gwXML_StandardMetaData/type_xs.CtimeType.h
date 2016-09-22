#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CtimeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CtimeType



namespace gie
{

namespace xs
{	

class CtimeType : public TypeBase
{
public:
	gie_EXPORT CtimeType(xercesc::DOMNode* const& init);
	gie_EXPORT CtimeType(CtimeType const& init);
	void operator=(CtimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CtimeType); }
	gie_EXPORT void operator=(const altova::DateTime& value);
	gie_EXPORT operator altova::DateTime();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CtimeType
