#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnonNegativeIntegerType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnonNegativeIntegerType



namespace gie
{

namespace xs
{	

class CnonNegativeIntegerType : public TypeBase
{
public:
	gie_EXPORT CnonNegativeIntegerType(xercesc::DOMNode* const& init);
	gie_EXPORT CnonNegativeIntegerType(CnonNegativeIntegerType const& init);
	void operator=(CnonNegativeIntegerType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CnonNegativeIntegerType); }
	gie_EXPORT void operator=(const unsigned __int64& value);
	gie_EXPORT operator unsigned __int64();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CnonNegativeIntegerType
