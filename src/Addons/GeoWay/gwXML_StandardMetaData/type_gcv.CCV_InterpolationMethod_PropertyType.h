#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_InterpolationMethod_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_InterpolationMethod_PropertyType



namespace gie
{

namespace gcv
{	

class CCV_InterpolationMethod_PropertyType : public TypeBase
{
public:
	gie_EXPORT CCV_InterpolationMethod_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_InterpolationMethod_PropertyType(CCV_InterpolationMethod_PropertyType const& init);
	void operator=(CCV_InterpolationMethod_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_InterpolationMethod_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_InterpolationMethod_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gcv_altova_CCV_InterpolationMethod_PropertyType_altova_CV_InterpolationMethod> CV_InterpolationMethod;
	struct CV_InterpolationMethod { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_InterpolationMethod_PropertyType
