#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdoubleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdoubleType



namespace gie
{

namespace xs
{	

class CdoubleType : public TypeBase
{
public:
	gie_EXPORT CdoubleType(xercesc::DOMNode* const& init);
	gie_EXPORT CdoubleType(CdoubleType const& init);
	void operator=(CdoubleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CdoubleType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT operator double();
	gie_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_xs_ALTOVA_CdoubleType
