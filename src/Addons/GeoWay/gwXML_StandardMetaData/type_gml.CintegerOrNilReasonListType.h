#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CintegerOrNilReasonListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CintegerOrNilReasonListType



namespace gie
{

namespace gml
{	

class CintegerOrNilReasonListType : public TypeBase
{
public:
	gie_EXPORT CintegerOrNilReasonListType(xercesc::DOMNode* const& init);
	gie_EXPORT CintegerOrNilReasonListType(CintegerOrNilReasonListType const& init);
	void operator=(CintegerOrNilReasonListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CintegerOrNilReasonListType); }

	enum EnumValues {
		Invalid = -1,
		k_inapplicable = 0, // inapplicable
		k_missing = 1, // missing
		k_template = 2, // template
		k_unknown = 3, // unknown
		k_withheld = 4, // withheld
		EnumValueCount
	};

	
	gie_EXPORT int GetEnumerationValue();
	gie_EXPORT void SetEnumerationValue( const int index);
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CintegerOrNilReasonListType
