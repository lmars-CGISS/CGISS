#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CactuateType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CactuateType



namespace gie
{

namespace gie2
{	

class CactuateType : public TypeBase
{
public:
	gie_EXPORT CactuateType(xercesc::DOMNode* const& init);
	gie_EXPORT CactuateType(CactuateType const& init);
	void operator=(CactuateType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gie2_altova_CactuateType); }

	enum EnumValues {
		Invalid = -1,
		k_onLoad = 0, // onLoad
		k_onRequest = 1, // onRequest
		k_other = 2, // other
		k_none = 3, // none
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CactuateType
