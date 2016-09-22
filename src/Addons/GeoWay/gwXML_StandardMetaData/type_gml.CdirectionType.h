#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdirectionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdirectionType



namespace gie
{

namespace gml
{	

class CdirectionType : public TypeBase
{
public:
	gie_EXPORT CdirectionType(xercesc::DOMNode* const& init);
	gie_EXPORT CdirectionType(CdirectionType const& init);
	void operator=(CdirectionType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CdirectionType); }

	enum EnumValues {
		Invalid = -1,
		k_N = 0, // N
		k_E = 1, // E
		k_S = 2, // S
		k_W = 3, // W
		k__ = 4, // +
		k__2 = 5, // -
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdirectionType
