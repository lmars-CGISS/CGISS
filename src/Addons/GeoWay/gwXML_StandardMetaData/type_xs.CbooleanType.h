#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CbooleanType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CbooleanType



namespace gie
{

namespace xs
{	

class CbooleanType : public TypeBase
{
public:
	gie_EXPORT CbooleanType(xercesc::DOMNode* const& init);
	gie_EXPORT CbooleanType(CbooleanType const& init);
	void operator=(CbooleanType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CbooleanType); }
	gie_EXPORT void operator=(const bool& value);
	gie_EXPORT operator bool();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CbooleanType
