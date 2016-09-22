#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcMinutesTypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcMinutesTypeType



namespace gie
{

namespace gml
{	

class CArcMinutesTypeType : public TypeBase
{
public:
	gie_EXPORT CArcMinutesTypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CArcMinutesTypeType(CArcMinutesTypeType const& init);
	void operator=(CArcMinutesTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CArcMinutesTypeType); }
	gie_EXPORT void operator=(const unsigned __int64& value);
	gie_EXPORT operator unsigned __int64();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcMinutesTypeType
