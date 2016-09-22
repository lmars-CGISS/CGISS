#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_SequenceRule_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_SequenceRule_PropertyType



namespace gie
{

namespace gcv
{	

class CCV_SequenceRule_PropertyType : public TypeBase
{
public:
	gie_EXPORT CCV_SequenceRule_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_SequenceRule_PropertyType(CCV_SequenceRule_PropertyType const& init);
	void operator=(CCV_SequenceRule_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_SequenceRule_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gcv::CCV_SequenceRule_Type, _altova_mi_gcv_altova_CCV_SequenceRule_PropertyType_altova_CV_SequenceRule> CV_SequenceRule;
	struct CV_SequenceRule { typedef Iterator<gcv::CCV_SequenceRule_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_SequenceRule_PropertyType
