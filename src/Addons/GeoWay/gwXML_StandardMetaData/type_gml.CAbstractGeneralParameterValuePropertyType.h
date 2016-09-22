#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralParameterValuePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralParameterValuePropertyType



namespace gie
{

namespace gml
{	

class CAbstractGeneralParameterValuePropertyType : public TypeBase
{
public:
	gie_EXPORT CAbstractGeneralParameterValuePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeneralParameterValuePropertyType(CAbstractGeneralParameterValuePropertyType const& init);
	void operator=(CAbstractGeneralParameterValuePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeneralParameterValuePropertyType); }
	MemberElement<gml::CParameterValueType, _altova_mi_gml_altova_CAbstractGeneralParameterValuePropertyType_altova_ParameterValue> ParameterValue;
	struct ParameterValue { typedef Iterator<gml::CParameterValueType> iterator; };
	MemberElement<gml::CParameterValueGroupType, _altova_mi_gml_altova_CAbstractGeneralParameterValuePropertyType_altova_ParameterValueGroup> ParameterValueGroup;
	struct ParameterValueGroup { typedef Iterator<gml::CParameterValueGroupType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralParameterValuePropertyType
