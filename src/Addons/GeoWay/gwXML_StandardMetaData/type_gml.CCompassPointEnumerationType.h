#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompassPointEnumerationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompassPointEnumerationType



namespace gie
{

namespace gml
{	

class CCompassPointEnumerationType : public TypeBase
{
public:
	gie_EXPORT CCompassPointEnumerationType(xercesc::DOMNode* const& init);
	gie_EXPORT CCompassPointEnumerationType(CCompassPointEnumerationType const& init);
	void operator=(CCompassPointEnumerationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCompassPointEnumerationType); }

	enum EnumValues {
		Invalid = -1,
		k_N = 0, // N
		k_NNE = 1, // NNE
		k_NE = 2, // NE
		k_ENE = 3, // ENE
		k_E = 4, // E
		k_ESE = 5, // ESE
		k_SE = 6, // SE
		k_SSE = 7, // SSE
		k_S = 8, // S
		k_SSW = 9, // SSW
		k_SW = 10, // SW
		k_WSW = 11, // WSW
		k_W = 12, // W
		k_WNW = 13, // WNW
		k_NW = 14, // NW
		k_NNW = 15, // NNW
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompassPointEnumerationType
