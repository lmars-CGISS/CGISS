#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileValueModelType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileValueModelType



namespace gie
{

namespace gml
{	

class CFileValueModelType : public TypeBase
{
public:
	gie_EXPORT CFileValueModelType(xercesc::DOMNode* const& init);
	gie_EXPORT CFileValueModelType(CFileValueModelType const& init);
	void operator=(CFileValueModelType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CFileValueModelType); }

	enum EnumValues {
		Invalid = -1,
		k_Record_Interleaved = 0, // Record Interleaved
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileValueModelType
