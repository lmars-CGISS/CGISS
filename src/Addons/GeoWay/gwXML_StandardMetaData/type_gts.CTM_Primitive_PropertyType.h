#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gts_ALTOVA_CTM_Primitive_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gts_ALTOVA_CTM_Primitive_PropertyType



namespace gie
{

namespace gts
{	

class CTM_Primitive_PropertyType : public TypeBase
{
public:
	gie_EXPORT CTM_Primitive_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTM_Primitive_PropertyType(CTM_Primitive_PropertyType const& init);
	void operator=(CTM_Primitive_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gts_altova_CTM_Primitive_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gcv::CTM_GeometricPrimitive_Type, _altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_TM_GeometricPrimitive> TM_GeometricPrimitive;
	struct TM_GeometricPrimitive { typedef Iterator<gcv::CTM_GeometricPrimitive_Type> iterator; };
	MemberElement<gcv::CTM_Period_Type, _altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_TM_Period> TM_Period;
	struct TM_Period { typedef Iterator<gcv::CTM_Period_Type> iterator; };
	MemberElement<gml::CTimeEdgeType, _altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_TimeEdge> TimeEdge;
	struct TimeEdge { typedef Iterator<gml::CTimeEdgeType> iterator; };
	MemberElement<gml::CTimeInstantType, _altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_TimeInstant> TimeInstant;
	struct TimeInstant { typedef Iterator<gml::CTimeInstantType> iterator; };
	MemberElement<gml::CTimeNodeType, _altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_TimeNode> TimeNode;
	struct TimeNode { typedef Iterator<gml::CTimeNodeType> iterator; };
	MemberElement<gml::CTimePeriodType, _altova_mi_gts_altova_CTM_Primitive_PropertyType_altova_TimePeriod> TimePeriod;
	struct TimePeriod { typedef Iterator<gml::CTimePeriodType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gts

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gts_ALTOVA_CTM_Primitive_PropertyType
