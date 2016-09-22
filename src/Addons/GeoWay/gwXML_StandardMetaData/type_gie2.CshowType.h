#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CshowType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CshowType



namespace gie
{

namespace gie2
{	

class CshowType : public TypeBase
{
public:
	gie_EXPORT CshowType(xercesc::DOMNode* const& init);
	gie_EXPORT CshowType(CshowType const& init);
	void operator=(CshowType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gie2_altova_CshowType); }

	enum EnumValues {
		Invalid = -1,
		k_new = 0, // new
		k_replace = 1, // replace
		k_embed = 2, // embed
		k_other = 3, // other
		k_none = 4, // none
		EnumValueCount
	};
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



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CshowType
