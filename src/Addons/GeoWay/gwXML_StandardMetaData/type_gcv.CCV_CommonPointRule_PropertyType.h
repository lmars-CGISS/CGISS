#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_CommonPointRule_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_CommonPointRule_PropertyType



namespace gie
{

namespace gcv
{	

class CCV_CommonPointRule_PropertyType : public TypeBase
{
public:
	gie_EXPORT CCV_CommonPointRule_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_CommonPointRule_PropertyType(CCV_CommonPointRule_PropertyType const& init);
	void operator=(CCV_CommonPointRule_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_CommonPointRule_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_CommonPointRule_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gcv_altova_CCV_CommonPointRule_PropertyType_altova_CV_CommonPointRule> CV_CommonPointRule;
	struct CV_CommonPointRule { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_CommonPointRule_PropertyType
