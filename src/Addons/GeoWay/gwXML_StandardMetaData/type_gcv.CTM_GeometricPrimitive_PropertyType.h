#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_GeometricPrimitive_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_GeometricPrimitive_PropertyType



namespace gie
{

namespace gcv
{	

class CTM_GeometricPrimitive_PropertyType : public TypeBase
{
public:
	gie_EXPORT CTM_GeometricPrimitive_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTM_GeometricPrimitive_PropertyType(CTM_GeometricPrimitive_PropertyType const& init);
	void operator=(CTM_GeometricPrimitive_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CTM_GeometricPrimitive_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gcv::CTM_GeometricPrimitive_Type, _altova_mi_gcv_altova_CTM_GeometricPrimitive_PropertyType_altova_TM_GeometricPrimitive> TM_GeometricPrimitive;
	struct TM_GeometricPrimitive { typedef Iterator<gcv::CTM_GeometricPrimitive_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTM_GeometricPrimitive_PropertyType
