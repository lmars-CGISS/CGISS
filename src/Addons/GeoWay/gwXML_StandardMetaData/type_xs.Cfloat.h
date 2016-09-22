#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cfloat
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cfloat



namespace gie
{

namespace xs
{	

class Cfloat : public TypeBase
{
public:
	gie_EXPORT Cfloat(xercesc::DOMNode* const& init);
	gie_EXPORT Cfloat(Cfloat const& init);
	void operator=(Cfloat const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cfloat); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cfloat
