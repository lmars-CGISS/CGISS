#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cbase64Binary
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cbase64Binary



namespace gie
{

namespace xs
{	

class Cbase64Binary : public TypeBase
{
public:
	gie_EXPORT Cbase64Binary(xercesc::DOMNode* const& init);
	gie_EXPORT Cbase64Binary(Cbase64Binary const& init);
	void operator=(Cbase64Binary const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cbase64Binary); }
	void operator= (const std::vector<unsigned char>& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator std::vector<unsigned char>()
	{
		return CastAs<std::vector<unsigned char> >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cbase64Binary
