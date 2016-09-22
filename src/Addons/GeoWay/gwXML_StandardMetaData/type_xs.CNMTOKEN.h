#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CNMTOKEN
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CNMTOKEN



namespace gie
{

namespace xs
{	

class CNMTOKEN : public TypeBase
{
public:
	gie_EXPORT CNMTOKEN(xercesc::DOMNode* const& init);
	gie_EXPORT CNMTOKEN(CNMTOKEN const& init);
	void operator=(CNMTOKEN const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CNMTOKEN); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CNMTOKEN
