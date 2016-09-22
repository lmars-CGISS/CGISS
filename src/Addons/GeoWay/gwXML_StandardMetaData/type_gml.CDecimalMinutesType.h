#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDecimalMinutesType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDecimalMinutesType



namespace gie
{

namespace gml
{	

class CDecimalMinutesType : public TypeBase
{
public:
	gie_EXPORT CDecimalMinutesType(xercesc::DOMNode* const& init);
	gie_EXPORT CDecimalMinutesType(CDecimalMinutesType const& init);
	void operator=(CDecimalMinutesType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CDecimalMinutesType); }
	void operator= (const double& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DecimalFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator double()
	{
		return CastAs<double >::Do(GetNode(), 0);
	}
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDecimalMinutesType
