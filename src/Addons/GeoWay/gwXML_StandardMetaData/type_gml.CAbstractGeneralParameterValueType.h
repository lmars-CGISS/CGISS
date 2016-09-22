#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralParameterValueType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralParameterValueType



namespace gie
{

namespace gml
{	

class CAbstractGeneralParameterValueType : public TypeBase
{
public:
	gie_EXPORT CAbstractGeneralParameterValueType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeneralParameterValueType(CAbstractGeneralParameterValueType const& init);
	void operator=(CAbstractGeneralParameterValueType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeneralParameterValueType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralParameterValueType
