#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDate_TypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDate_TypeType



namespace gie
{

namespace gco
{	

class CDate_TypeType : public TypeBase
{
public:
	gie_EXPORT CDate_TypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CDate_TypeType(CDate_TypeType const& init);
	void operator=(CDate_TypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CDate_TypeType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CDate_TypeType
