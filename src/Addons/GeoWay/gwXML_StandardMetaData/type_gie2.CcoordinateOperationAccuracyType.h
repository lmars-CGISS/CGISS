#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CcoordinateOperationAccuracyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CcoordinateOperationAccuracyType



namespace gie
{

namespace gie2
{	

class CcoordinateOperationAccuracyType : public TypeBase
{
public:
	gie_EXPORT CcoordinateOperationAccuracyType(xercesc::DOMNode* const& init);
	gie_EXPORT CcoordinateOperationAccuracyType(CcoordinateOperationAccuracyType const& init);
	void operator=(CcoordinateOperationAccuracyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CcoordinateOperationAccuracyType); }

	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gmd::CDQ_AbsoluteExternalPositionalAccuracy_Type, _altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_DQ_AbsoluteExternalPositionalAccuracy> DQ_AbsoluteExternalPositionalAccuracy;
	struct DQ_AbsoluteExternalPositionalAccuracy { typedef Iterator<gmd::CDQ_AbsoluteExternalPositionalAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_GriddedDataPositionalAccuracy_Type, _altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_DQ_GriddedDataPositionalAccuracy> DQ_GriddedDataPositionalAccuracy;
	struct DQ_GriddedDataPositionalAccuracy { typedef Iterator<gmd::CDQ_GriddedDataPositionalAccuracy_Type> iterator; };
	MemberElement<gmd::CDQ_RelativeInternalPositionalAccuracy_Type, _altova_mi_gie2_altova_CcoordinateOperationAccuracyType_altova_DQ_RelativeInternalPositionalAccuracy> DQ_RelativeInternalPositionalAccuracy;
	struct DQ_RelativeInternalPositionalAccuracy { typedef Iterator<gmd::CDQ_RelativeInternalPositionalAccuracy_Type> iterator; };
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CcoordinateOperationAccuracyType
