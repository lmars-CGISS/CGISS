#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CbooleanOrNilReasonType2
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CbooleanOrNilReasonType2



namespace gie
{

namespace gml
{	

class CbooleanOrNilReasonType2 : public TypeBase
{
public:
	gie_EXPORT CbooleanOrNilReasonType2(xercesc::DOMNode* const& init);
	gie_EXPORT CbooleanOrNilReasonType2(CbooleanOrNilReasonType2 const& init);
	void operator=(CbooleanOrNilReasonType2 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CbooleanOrNilReasonType2); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CbooleanOrNilReasonType2
