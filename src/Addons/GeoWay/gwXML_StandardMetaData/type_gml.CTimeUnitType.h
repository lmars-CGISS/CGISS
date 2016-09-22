#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeUnitType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeUnitType



namespace gie
{

namespace gml
{	

class CTimeUnitType : public TypeBase
{
public:
	gie_EXPORT CTimeUnitType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeUnitType(CTimeUnitType const& init);
	void operator=(CTimeUnitType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CTimeUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_year = 0, // year
		k_month = 1, // month
		k_day = 2, // day
		k_hour = 3, // hour
		k_minute = 4, // minute
		k_second = 5, // second
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeUnitType
