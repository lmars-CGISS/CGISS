#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CunsignedByte
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CunsignedByte



namespace gie
{

namespace xs
{	

class CunsignedByte : public TypeBase
{
public:
	gie_EXPORT CunsignedByte(xercesc::DOMNode* const& init);
	gie_EXPORT CunsignedByte(CunsignedByte const& init);
	void operator=(CunsignedByte const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CunsignedByte); }
	void operator= (const unsigned& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator unsigned()
	{
		return CastAs<unsigned >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CunsignedByte
