#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cshort
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cshort



namespace gie
{

namespace xs
{	

class Cshort : public TypeBase
{
public:
	gie_EXPORT Cshort(xercesc::DOMNode* const& init);
	gie_EXPORT Cshort(Cshort const& init);
	void operator=(Cshort const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cshort); }
	void operator= (const int& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator int()
	{
		return CastAs<int >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cshort
