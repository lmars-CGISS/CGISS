#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_PriorityCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_PriorityCode_PropertyType



namespace gie
{

namespace gmi
{	

class CMI_PriorityCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMI_PriorityCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_PriorityCode_PropertyType(CMI_PriorityCode_PropertyType const& init);
	void operator=(CMI_PriorityCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_PriorityCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_PriorityCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmi_altova_CMI_PriorityCode_PropertyType_altova_MI_PriorityCode> MI_PriorityCode;
	struct MI_PriorityCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_PriorityCode_PropertyType
