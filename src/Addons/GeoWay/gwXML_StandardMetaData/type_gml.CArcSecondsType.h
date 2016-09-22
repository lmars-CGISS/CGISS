#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcSecondsType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcSecondsType



namespace gie
{

namespace gml
{	

class CArcSecondsType : public TypeBase
{
public:
	gie_EXPORT CArcSecondsType(xercesc::DOMNode* const& init);
	gie_EXPORT CArcSecondsType(CArcSecondsType const& init);
	void operator=(CArcSecondsType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CArcSecondsType); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcSecondsType
