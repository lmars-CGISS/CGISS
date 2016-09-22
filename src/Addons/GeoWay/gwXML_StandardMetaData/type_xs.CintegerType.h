#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CintegerType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CintegerType



namespace gie
{

namespace xs
{	

class CintegerType : public TypeBase
{
public:
	gie_EXPORT CintegerType(xercesc::DOMNode* const& init);
	gie_EXPORT CintegerType(CintegerType const& init);
	void operator=(CintegerType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CintegerType); }
	gie_EXPORT void operator=(const __int64& value);
	gie_EXPORT operator __int64();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CintegerType
