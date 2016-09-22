#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPassThroughOperationPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPassThroughOperationPropertyType



namespace gie
{

namespace gml
{	

class CPassThroughOperationPropertyType : public TypeBase
{
public:
	gie_EXPORT CPassThroughOperationPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CPassThroughOperationPropertyType(CPassThroughOperationPropertyType const& init);
	void operator=(CPassThroughOperationPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPassThroughOperationPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CPassThroughOperationType, _altova_mi_gml_altova_CPassThroughOperationPropertyType_altova_PassThroughOperation> PassThroughOperation;
	struct PassThroughOperation { typedef Iterator<gml::CPassThroughOperationType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPassThroughOperationPropertyType
