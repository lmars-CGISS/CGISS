#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRangeParametersType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRangeParametersType



namespace gie
{

namespace gml
{	

class CRangeParametersType : public TypeBase
{
public:
	gie_EXPORT CRangeParametersType(xercesc::DOMNode* const& init);
	gie_EXPORT CRangeParametersType(CRangeParametersType const& init);
	void operator=(CRangeParametersType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRangeParametersType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CRangeParametersType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CRangeParametersType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gie2::CBooleanType, _altova_mi_gml_altova_CRangeParametersType_altova_Boolean> Boolean;
	struct Boolean { typedef Iterator<gie2::CBooleanType> iterator; };
	MemberElement<gml::CbooleanOrNilReasonListType, _altova_mi_gml_altova_CRangeParametersType_altova_BooleanList> BooleanList;
	struct BooleanList { typedef Iterator<gml::CbooleanOrNilReasonListType> iterator; };
	MemberElement<gie2::CCategoryType, _altova_mi_gml_altova_CRangeParametersType_altova_Category> Category;
	struct Category { typedef Iterator<gie2::CCategoryType> iterator; };
	MemberElement<gml::CCategoryExtentType, _altova_mi_gml_altova_CRangeParametersType_altova_CategoryExtent> CategoryExtent;
	struct CategoryExtent { typedef Iterator<gml::CCategoryExtentType> iterator; };
	MemberElement<gml::CCodeOrNilReasonListType, _altova_mi_gml_altova_CRangeParametersType_altova_CategoryList> CategoryList;
	struct CategoryList { typedef Iterator<gml::CCodeOrNilReasonListType> iterator; };
	MemberElement<gml::CCompositeValueType, _altova_mi_gml_altova_CRangeParametersType_altova_CompositeValue> CompositeValue;
	struct CompositeValue { typedef Iterator<gml::CCompositeValueType> iterator; };
	MemberElement<gie2::CCountType, _altova_mi_gml_altova_CRangeParametersType_altova_Count> Count;
	struct Count { typedef Iterator<gie2::CCountType> iterator; };
	MemberElement<gml::CCountExtentTypeType, _altova_mi_gml_altova_CRangeParametersType_altova_CountExtent> CountExtent;
	struct CountExtent { typedef Iterator<gml::CCountExtentTypeType> iterator; };
	MemberElement<gml::CintegerOrNilReasonListType, _altova_mi_gml_altova_CRangeParametersType_altova_CountList> CountList;
	struct CountList { typedef Iterator<gml::CintegerOrNilReasonListType> iterator; };
	MemberElement<gie2::CQuantityType, _altova_mi_gml_altova_CRangeParametersType_altova_Quantity> Quantity;
	struct Quantity { typedef Iterator<gie2::CQuantityType> iterator; };
	MemberElement<gml::CQuantityExtentType, _altova_mi_gml_altova_CRangeParametersType_altova_QuantityExtent> QuantityExtent;
	struct QuantityExtent { typedef Iterator<gml::CQuantityExtentType> iterator; };
	MemberElement<gml::CMeasureOrNilReasonListType, _altova_mi_gml_altova_CRangeParametersType_altova_QuantityList> QuantityList;
	struct QuantityList { typedef Iterator<gml::CMeasureOrNilReasonListType> iterator; };
	MemberElement<gml::CValueArrayType, _altova_mi_gml_altova_CRangeParametersType_altova_ValueArray> ValueArray;
	struct ValueArray { typedef Iterator<gml::CValueArrayType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRangeParametersType
