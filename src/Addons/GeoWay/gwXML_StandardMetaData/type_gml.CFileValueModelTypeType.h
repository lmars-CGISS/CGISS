#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileValueModelTypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileValueModelTypeType



namespace gie
{

namespace gml
{	

class CFileValueModelTypeType : public TypeBase
{
public:
	gie_EXPORT CFileValueModelTypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CFileValueModelTypeType(CFileValueModelTypeType const& init);
	void operator=(CFileValueModelTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFileValueModelTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_Record_Interleaved = 0, // Record Interleaved
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileValueModelTypeType
