#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_TransferFunctionTypeCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_TransferFunctionTypeCode_PropertyType



namespace gie
{

namespace gmi
{	

class CMI_TransferFunctionTypeCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMI_TransferFunctionTypeCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_TransferFunctionTypeCode_PropertyType(CMI_TransferFunctionTypeCode_PropertyType const& init);
	void operator=(CMI_TransferFunctionTypeCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_TransferFunctionTypeCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_TransferFunctionTypeCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmi_altova_CMI_TransferFunctionTypeCode_PropertyType_altova_MI_TransferFunctionTypeCode> MI_TransferFunctionTypeCode;
	struct MI_TransferFunctionTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_TransferFunctionTypeCode_PropertyType
