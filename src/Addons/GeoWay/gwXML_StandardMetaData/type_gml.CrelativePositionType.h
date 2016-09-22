#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrelativePositionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrelativePositionType



namespace gie
{

namespace gml
{	

class CrelativePositionType : public TypeBase
{
public:
	gie_EXPORT CrelativePositionType(xercesc::DOMNode* const& init);
	gie_EXPORT CrelativePositionType(CrelativePositionType const& init);
	void operator=(CrelativePositionType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CrelativePositionType); }

	enum EnumValues {
		Invalid = -1,
		k_Before = 0, // Before
		k_After = 1, // After
		k_Begins = 2, // Begins
		k_Ends = 3, // Ends
		k_During = 4, // During
		k_Equals = 5, // Equals
		k_Contains = 6, // Contains
		k_Overlaps = 7, // Overlaps
		k_Meets = 8, // Meets
		k_OverlappedBy = 9, // OverlappedBy
		k_MetBy = 10, // MetBy
		k_BegunBy = 11, // BegunBy
		k_EndedBy = 12, // EndedBy
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CrelativePositionType
