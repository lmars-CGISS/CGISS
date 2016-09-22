#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePositionUnionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePositionUnionType



namespace gie
{

namespace gml
{	

class CTimePositionUnionType : public TypeBase
{
public:
	gie_EXPORT CTimePositionUnionType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimePositionUnionType(CTimePositionUnionType const& init);
	void operator=(CTimePositionUnionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimePositionUnionType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePositionUnionType
