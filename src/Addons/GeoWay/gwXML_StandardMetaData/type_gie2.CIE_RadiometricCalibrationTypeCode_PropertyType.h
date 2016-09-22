#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_RadiometricCalibrationTypeCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_RadiometricCalibrationTypeCode_PropertyType



namespace gie
{

namespace gie2
{	

class CIE_RadiometricCalibrationTypeCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CIE_RadiometricCalibrationTypeCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_RadiometricCalibrationTypeCode_PropertyType(CIE_RadiometricCalibrationTypeCode_PropertyType const& init);
	void operator=(CIE_RadiometricCalibrationTypeCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_RadiometricCalibrationTypeCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_RadiometricCalibrationTypeCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gie2_altova_CIE_RadiometricCalibrationTypeCode_PropertyType_altova_IE_RadiometricCalibrationTypeCode> IE_RadiometricCalibrationTypeCode;
	struct IE_RadiometricCalibrationTypeCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_RadiometricCalibrationTypeCode_PropertyType
