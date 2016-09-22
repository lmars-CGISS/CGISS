#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Ctime
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Ctime



namespace gie
{

namespace xs
{	

class Ctime : public TypeBase
{
public:
	gie_EXPORT Ctime(xercesc::DOMNode* const& init);
	gie_EXPORT Ctime(Ctime const& init);
	void operator=(Ctime const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Ctime); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::TimeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Ctime
