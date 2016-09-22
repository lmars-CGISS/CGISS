#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcMinutesType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcMinutesType



namespace gie
{

namespace gml
{	

class CArcMinutesType : public TypeBase
{
public:
	gie_EXPORT CArcMinutesType(xercesc::DOMNode* const& init);
	gie_EXPORT CArcMinutesType(CArcMinutesType const& init);
	void operator=(CArcMinutesType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CArcMinutesType); }
	void operator= (const unsigned __int64& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator unsigned __int64()
	{
		return CastAs<unsigned __int64 >::Do(GetNode(), 0);
	}
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcMinutesType
