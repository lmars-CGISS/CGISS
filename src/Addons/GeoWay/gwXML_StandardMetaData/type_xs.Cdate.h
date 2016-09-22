#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdate
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdate



namespace gie
{

namespace xs
{	

class Cdate : public TypeBase
{
public:
	gie_EXPORT Cdate(xercesc::DOMNode* const& init);
	gie_EXPORT Cdate(Cdate const& init);
	void operator=(Cdate const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cdate); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DateFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_Cdate
