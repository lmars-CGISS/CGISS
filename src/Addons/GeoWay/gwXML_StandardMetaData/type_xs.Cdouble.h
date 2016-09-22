#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdouble
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdouble



namespace gie
{

namespace xs
{	

class Cdouble : public TypeBase
{
public:
	gie_EXPORT Cdouble(xercesc::DOMNode* const& init);
	gie_EXPORT Cdouble(Cdouble const& init);
	void operator=(Cdouble const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cdouble); }
	void operator= (const double& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DoubleFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator double()
	{
		return CastAs<double >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdouble
