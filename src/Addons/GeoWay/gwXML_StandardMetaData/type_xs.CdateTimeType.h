#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdateTimeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdateTimeType



namespace gie
{

namespace xs
{	

class CdateTimeType : public TypeBase
{
public:
	gie_EXPORT CdateTimeType(xercesc::DOMNode* const& init);
	gie_EXPORT CdateTimeType(CdateTimeType const& init);
	void operator=(CdateTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CdateTimeType); }
	gie_EXPORT void operator=(const altova::DateTime& value);
	gie_EXPORT operator altova::DateTime();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdateTimeType
