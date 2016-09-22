#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnonPositiveInteger
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnonPositiveInteger



namespace gie
{

namespace xs
{	

class CnonPositiveInteger : public TypeBase
{
public:
	gie_EXPORT CnonPositiveInteger(xercesc::DOMNode* const& init);
	gie_EXPORT CnonPositiveInteger(CnonPositiveInteger const& init);
	void operator=(CnonPositiveInteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnonPositiveInteger); }
	void operator= (const __int64& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator __int64()
	{
		return CastAs<__int64 >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnonPositiveInteger
