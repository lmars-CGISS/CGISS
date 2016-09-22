#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSignType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSignType



namespace gie
{

namespace gml
{	

class CSignType : public TypeBase
{
public:
	gie_EXPORT CSignType(xercesc::DOMNode* const& init);
	gie_EXPORT CSignType(CSignType const& init);
	void operator=(CSignType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CSignType); }

	enum EnumValues {
		Invalid = -1,
		k__ = 0, // -
		k__2 = 1, // +
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSignType
