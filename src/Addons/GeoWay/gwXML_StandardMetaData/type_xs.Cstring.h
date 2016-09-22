#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cstring
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cstring



namespace gie
{

namespace xs
{	

class Cstring : public TypeBase
{
public:
	gie_EXPORT Cstring(xercesc::DOMNode* const& init);
	gie_EXPORT Cstring(Cstring const& init);
	void operator=(Cstring const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cstring); }
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cstring
