#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDecimalMinutesTypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDecimalMinutesTypeType



namespace gie
{

namespace gml
{	

class CDecimalMinutesTypeType : public TypeBase
{
public:
	gie_EXPORT CDecimalMinutesTypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CDecimalMinutesTypeType(CDecimalMinutesTypeType const& init);
	void operator=(CDecimalMinutesTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDecimalMinutesTypeType); }
	gie_EXPORT void operator=(const double& value);
	gie_EXPORT operator double();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDecimalMinutesTypeType
