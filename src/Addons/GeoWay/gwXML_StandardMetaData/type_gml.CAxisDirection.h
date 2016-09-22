#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAxisDirection
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAxisDirection



namespace gie
{

namespace gml
{	

class CAxisDirection : public TypeBase
{
public:
	gie_EXPORT CAxisDirection(xercesc::DOMNode* const& init);
	gie_EXPORT CAxisDirection(CAxisDirection const& init);
	void operator=(CAxisDirection const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CAxisDirection); }
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAxisDirection
