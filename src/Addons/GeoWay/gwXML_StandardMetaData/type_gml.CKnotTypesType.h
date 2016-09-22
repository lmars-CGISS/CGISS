#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CKnotTypesType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CKnotTypesType



namespace gie
{

namespace gml
{	

class CKnotTypesType : public TypeBase
{
public:
	gie_EXPORT CKnotTypesType(xercesc::DOMNode* const& init);
	gie_EXPORT CKnotTypesType(CKnotTypesType const& init);
	void operator=(CKnotTypesType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CKnotTypesType); }

	enum EnumValues {
		Invalid = -1,
		k_uniform = 0, // uniform
		k_quasiUniform = 1, // quasiUniform
		k_piecewiseBezier = 2, // piecewiseBezier
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CKnotTypesType
