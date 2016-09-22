#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSuccessionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSuccessionType



namespace gie
{

namespace gml
{	

class CSuccessionType : public TypeBase
{
public:
	gie_EXPORT CSuccessionType(xercesc::DOMNode* const& init);
	gie_EXPORT CSuccessionType(CSuccessionType const& init);
	void operator=(CSuccessionType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CSuccessionType); }

	enum EnumValues {
		Invalid = -1,
		k_substitution = 0, // substitution
		k_division = 1, // division
		k_fusion = 2, // fusion
		k_initiation = 3, // initiation
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSuccessionType
