#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CpositiveIntegerType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CpositiveIntegerType



namespace gie
{

namespace xs
{	

class CpositiveIntegerType : public TypeBase
{
public:
	gie_EXPORT CpositiveIntegerType(xercesc::DOMNode* const& init);
	gie_EXPORT CpositiveIntegerType(CpositiveIntegerType const& init);
	void operator=(CpositiveIntegerType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CpositiveIntegerType); }
	gie_EXPORT void operator=(const unsigned __int64& value);
	gie_EXPORT operator unsigned __int64();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CpositiveIntegerType
