#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cboolean
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cboolean



namespace gie
{

namespace xs
{	

class Cboolean : public TypeBase
{
public:
	gie_EXPORT Cboolean(xercesc::DOMNode* const& init);
	gie_EXPORT Cboolean(Cboolean const& init);
	void operator=(Cboolean const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cboolean); }
	void operator= (const bool& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator bool()
	{
		return CastAs<bool >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cboolean
