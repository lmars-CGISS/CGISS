#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePrimitivePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePrimitivePropertyType



namespace gie
{

namespace gml
{	

class CTimePrimitivePropertyType : public TypeBase
{
public:
	gie_EXPORT CTimePrimitivePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimePrimitivePropertyType(CTimePrimitivePropertyType const& init);
	void operator=(CTimePrimitivePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimePrimitivePropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI

	MemberAttribute<bool,_altova_mi_gml_altova_CTimePrimitivePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gcv::CTM_GeometricPrimitive_Type, _altova_mi_gml_altova_CTimePrimitivePropertyType_altova_TM_GeometricPrimitive> TM_GeometricPrimitive;
	struct TM_GeometricPrimitive { typedef Iterator<gcv::CTM_GeometricPrimitive_Type> iterator; };
	MemberElement<gcv::CTM_Period_Type, _altova_mi_gml_altova_CTimePrimitivePropertyType_altova_TM_Period> TM_Period;
	struct TM_Period { typedef Iterator<gcv::CTM_Period_Type> iterator; };
	MemberElement<gml::CTimeEdgeType, _altova_mi_gml_altova_CTimePrimitivePropertyType_altova_TimeEdge> TimeEdge;
	struct TimeEdge { typedef Iterator<gml::CTimeEdgeType> iterator; };
	MemberElement<gml::CTimeInstantType, _altova_mi_gml_altova_CTimePrimitivePropertyType_altova_TimeInstant> TimeInstant;
	struct TimeInstant { typedef Iterator<gml::CTimeInstantType> iterator; };
	MemberElement<gml::CTimeNodeType, _altova_mi_gml_altova_CTimePrimitivePropertyType_altova_TimeNode> TimeNode;
	struct TimeNode { typedef Iterator<gml::CTimeNodeType> iterator; };
	MemberElement<gml::CTimePeriodType, _altova_mi_gml_altova_CTimePrimitivePropertyType_altova_TimePeriod> TimePeriod;
	struct TimePeriod { typedef Iterator<gml::CTimePeriodType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimePrimitivePropertyType
