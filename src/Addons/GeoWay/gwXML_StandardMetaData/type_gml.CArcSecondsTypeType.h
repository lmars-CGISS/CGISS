#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcSecondsTypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcSecondsTypeType



namespace gie
{

namespace gml
{	

class CArcSecondsTypeType : public TypeBase
{
public:
	gie_EXPORT CArcSecondsTypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CArcSecondsTypeType(CArcSecondsTypeType const& init);
	void operator=(CArcSecondsTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CArcSecondsTypeType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT operator double();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcSecondsTypeType
