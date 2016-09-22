#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdecimal
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdecimal



namespace gie
{

namespace xs
{	

class Cdecimal : public TypeBase
{
public:
	gie_EXPORT Cdecimal(xercesc::DOMNode* const& init);
	gie_EXPORT Cdecimal(Cdecimal const& init);
	void operator=(Cdecimal const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cdecimal); }
	void operator= (const double& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DecimalFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator double()
	{
		return CastAs<double >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdecimal
