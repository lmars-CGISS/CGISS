#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CNCName
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CNCName



namespace gie
{

namespace xs
{	

class CNCName : public TypeBase
{
public:
	gie_EXPORT CNCName(xercesc::DOMNode* const& init);
	gie_EXPORT CNCName(CNCName const& init);
	void operator=(CNCName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CNCName); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CNCName