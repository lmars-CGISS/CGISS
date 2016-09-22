#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAggregationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAggregationType



namespace gie
{

namespace gml
{	

class CAggregationType : public TypeBase
{
public:
	gie_EXPORT CAggregationType(xercesc::DOMNode* const& init);
	gie_EXPORT CAggregationType(CAggregationType const& init);
	void operator=(CAggregationType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CAggregationType); }

	enum EnumValues {
		Invalid = -1,
		k_set = 0, // set
		k_bag = 1, // bag
		k_sequence = 2, // sequence
		k_array = 3, // array
		k_record = 4, // record
		k_table = 5, // table
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAggregationType
