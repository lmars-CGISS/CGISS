#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdecimalType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdecimalType



namespace gie
{

namespace xs
{	

class CdecimalType : public TypeBase
{
public:
	gie_EXPORT CdecimalType(xercesc::DOMNode* const& init);
	gie_EXPORT CdecimalType(CdecimalType const& init);
	void operator=(CdecimalType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CdecimalType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT operator double();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdecimalType
