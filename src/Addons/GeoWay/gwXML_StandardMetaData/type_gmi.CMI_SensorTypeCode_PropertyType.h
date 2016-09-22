#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_SensorTypeCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_SensorTypeCode_PropertyType



namespace gie
{

namespace gmi
{	

class CMI_SensorTypeCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMI_SensorTypeCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMI_SensorTypeCode_PropertyType(CMI_SensorTypeCode_PropertyType const& init);
	void operator=(CMI_SensorTypeCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMI_SensorTypeCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmi_altova_CMI_SensorTypeCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmi_altova_CMI_SensorTypeCode_PropertyType_altova_MI_SensorTypeCode> MI_SensorTypeCode;
	struct MI_SensorTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMI_SensorTypeCode_PropertyType
