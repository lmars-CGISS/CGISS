#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnegativeInteger
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnegativeInteger



namespace gie
{

namespace xs
{	

class CnegativeInteger : public TypeBase
{
public:
	gie_EXPORT CnegativeInteger(xercesc::DOMNode* const& init);
	gie_EXPORT CnegativeInteger(CnegativeInteger const& init);
	void operator=(CnegativeInteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnegativeInteger); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnegativeInteger
