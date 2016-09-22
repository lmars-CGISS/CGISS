#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CisSphereType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CisSphereType



namespace gie
{

namespace gie2
{	

class CisSphereType : public TypeBase
{
public:
	gie_EXPORT CisSphereType(xercesc::DOMNode* const& init);
	gie_EXPORT CisSphereType(CisSphereType const& init);
	void operator=(CisSphereType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CisSphereType); }

	enum EnumValues {
		Invalid = -1,
		k_sphere = 0, // sphere
		EnumValueCount
	};

	
	gie_EXPORT int GetEnumerationValue();
	gie_EXPORT void SetEnumerationValue( const int index);
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CisSphereType
