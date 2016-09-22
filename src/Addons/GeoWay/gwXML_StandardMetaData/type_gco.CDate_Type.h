#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDate_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDate_Type



namespace gie
{

namespace gco
{	

class CDate_Type : public TypeBase
{
public:
	gie_EXPORT CDate_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CDate_Type(CDate_Type const& init);
	void operator=(CDate_Type const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gco_altova_CDate_Type); }
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



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDate_Type
