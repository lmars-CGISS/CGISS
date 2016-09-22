#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdoubleList
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdoubleList



namespace gie
{

namespace gml
{	

class CdoubleList : public TypeBase
{
public:
	gie_EXPORT CdoubleList(xercesc::DOMNode* const& init);
	gie_EXPORT CdoubleList(CdoubleList const& init);
	void operator=(CdoubleList const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CdoubleList); }
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdoubleList
