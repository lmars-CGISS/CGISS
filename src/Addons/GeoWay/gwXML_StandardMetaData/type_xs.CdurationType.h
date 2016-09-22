#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdurationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdurationType



namespace gie
{

namespace xs
{	

class CdurationType : public TypeBase
{
public:
	gie_EXPORT CdurationType(xercesc::DOMNode* const& init);
	gie_EXPORT CdurationType(CdurationType const& init);
	void operator=(CdurationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CdurationType); }
	gie_EXPORT void operator=(const altova::Duration& value);
	gie_EXPORT operator altova::Duration();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdurationType
