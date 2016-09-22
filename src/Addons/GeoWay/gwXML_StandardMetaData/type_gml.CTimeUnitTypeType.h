#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeUnitTypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeUnitTypeType



namespace gie
{

namespace gml
{	

class CTimeUnitTypeType : public TypeBase
{
public:
	gie_EXPORT CTimeUnitTypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeUnitTypeType(CTimeUnitTypeType const& init);
	void operator=(CTimeUnitTypeType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CTimeUnitTypeType); }

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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeUnitTypeType
