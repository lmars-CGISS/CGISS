#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNameOrNilReasonList
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNameOrNilReasonList



namespace gie
{

namespace gml
{	

class CNameOrNilReasonList : public TypeBase
{
public:
	gie_EXPORT CNameOrNilReasonList(xercesc::DOMNode* const& init);
	gie_EXPORT CNameOrNilReasonList(CNameOrNilReasonList const& init);
	void operator=(CNameOrNilReasonList const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CNameOrNilReasonList); }

	enum EnumValues {
		Invalid = -1,
		k_inapplicable = 0, // inapplicable
		k_missing = 1, // missing
		k_template = 2, // template
		k_unknown = 3, // unknown
		k_withheld = 4, // withheld
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CNameOrNilReasonList
