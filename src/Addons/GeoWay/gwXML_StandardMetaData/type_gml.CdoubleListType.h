#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdoubleListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdoubleListType



namespace gie
{

namespace gml
{	

class CdoubleListType : public TypeBase
{
public:
	gie_EXPORT CdoubleListType(xercesc::DOMNode* const& init);
	gie_EXPORT CdoubleListType(CdoubleListType const& init);
	void operator=(CdoubleListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CdoubleListType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CdoubleListType
