#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdateType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdateType



namespace gie
{

namespace xs
{	

class CdateType : public TypeBase
{
public:
	gie_EXPORT CdateType(xercesc::DOMNode* const& init);
	gie_EXPORT CdateType(CdateType const& init);
	void operator=(CdateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CdateType); }
	gie_EXPORT void operator=(const altova::DateTime& value);
	gie_EXPORT operator altova::DateTime();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdateType
