#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CstringOrNilReasonType2
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CstringOrNilReasonType2



namespace gie
{

namespace gml
{	

class CstringOrNilReasonType2 : public TypeBase
{
public:
	gie_EXPORT CstringOrNilReasonType2(xercesc::DOMNode* const& init);
	gie_EXPORT CstringOrNilReasonType2(CstringOrNilReasonType2 const& init);
	void operator=(CstringOrNilReasonType2 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CstringOrNilReasonType2); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CstringOrNilReasonType2
