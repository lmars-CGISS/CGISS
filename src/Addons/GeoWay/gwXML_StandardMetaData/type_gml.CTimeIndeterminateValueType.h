#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeIndeterminateValueType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeIndeterminateValueType



namespace gie
{

namespace gml
{	

class CTimeIndeterminateValueType : public TypeBase
{
public:
	gie_EXPORT CTimeIndeterminateValueType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeIndeterminateValueType(CTimeIndeterminateValueType const& init);
	void operator=(CTimeIndeterminateValueType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CTimeIndeterminateValueType); }

	enum EnumValues {
		Invalid = -1,
		k_after = 0, // after
		k_before = 1, // before
		k_now = 2, // now
		k_unknown = 3, // unknown
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



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeIndeterminateValueType
