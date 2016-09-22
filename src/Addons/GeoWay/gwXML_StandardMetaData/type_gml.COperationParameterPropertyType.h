#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COperationParameterPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COperationParameterPropertyType



namespace gie
{

namespace gml
{	

class COperationParameterPropertyType : public TypeBase
{
public:
	gie_EXPORT COperationParameterPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT COperationParameterPropertyType(COperationParameterPropertyType const& init);
	void operator=(COperationParameterPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_COperationParameterPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_COperationParameterPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::COperationParameterType, _altova_mi_gml_altova_COperationParameterPropertyType_altova_OperationParameter> OperationParameter;
	struct OperationParameter { typedef Iterator<gml::COperationParameterType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COperationParameterPropertyType
