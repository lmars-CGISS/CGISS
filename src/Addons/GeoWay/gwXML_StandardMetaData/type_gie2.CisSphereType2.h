#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CisSphereType2
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CisSphereType2



namespace gie
{

namespace gie2
{	

class CisSphereType2 : public TypeBase
{
public:
	gie_EXPORT CisSphereType2(xercesc::DOMNode* const& init);
	gie_EXPORT CisSphereType2(CisSphereType2 const& init);
	void operator=(CisSphereType2 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gie2_altova_CisSphereType2); }

	enum EnumValues {
		Invalid = -1,
		k_sphere = 0, // sphere
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CisSphereType2
