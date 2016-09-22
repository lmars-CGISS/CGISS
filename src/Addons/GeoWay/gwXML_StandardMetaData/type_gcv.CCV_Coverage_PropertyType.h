#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_Coverage_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_Coverage_PropertyType



namespace gie
{

namespace gcv
{	

class CCV_Coverage_PropertyType : public TypeBase
{
public:
	gie_EXPORT CCV_Coverage_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_Coverage_PropertyType(CCV_Coverage_PropertyType const& init);
	void operator=(CCV_Coverage_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_Coverage_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gcv::CCV_Coverage_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_CV_Coverage> CV_Coverage;
	struct CV_Coverage { typedef Iterator<gcv::CCV_Coverage_Type> iterator; };
	MemberElement<gie2::CIE_ActiveMWData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_ActiveMWData> IE_ActiveMWData;
	struct IE_ActiveMWData { typedef Iterator<gie2::CIE_ActiveMWData_Type> iterator; };
	MemberElement<gie2::CIE_CategoricalGriddedData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_CategoricalGriddedData> IE_CategoricalGriddedData;
	struct IE_CategoricalGriddedData { typedef Iterator<gie2::CIE_CategoricalGriddedData_Type> iterator; };
	MemberElement<gie2::CIE_FusedImage_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_FusedImage> IE_FusedImage;
	struct IE_FusedImage { typedef Iterator<gie2::CIE_FusedImage_Type> iterator; };
	MemberElement<gie2::CIE_NumericalGriddedData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_NumericalGriddedData> IE_NumericalGriddedData;
	struct IE_NumericalGriddedData { typedef Iterator<gie2::CIE_NumericalGriddedData_Type> iterator; };
	MemberElement<gie2::CIE_OpticalImage_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_OpticalImage> IE_OpticalImage;
	struct IE_OpticalImage { typedef Iterator<gie2::CIE_OpticalImage_Type> iterator; };
	MemberElement<gie2::CIE_PassiveMWData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_PassiveMWData> IE_PassiveMWData;
	struct IE_PassiveMWData { typedef Iterator<gie2::CIE_PassiveMWData_Type> iterator; };
	MemberElement<gie2::CIE_RadiometerData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_RadiometerData> IE_RadiometerData;
	struct IE_RadiometerData { typedef Iterator<gie2::CIE_RadiometerData_Type> iterator; };
	MemberElement<gie2::CIE_SARAmplitudeData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_SARAmplitudeData> IE_SARAmplitudeData;
	struct IE_SARAmplitudeData { typedef Iterator<gie2::CIE_SARAmplitudeData_Type> iterator; };
	MemberElement<gie2::CIE_SARComplexData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_SARComplexData> IE_SARComplexData;
	struct IE_SARComplexData { typedef Iterator<gie2::CIE_SARComplexData_Type> iterator; };
	MemberElement<gie2::CIE_SARData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_SARData> IE_SARData;
	struct IE_SARData { typedef Iterator<gie2::CIE_SARData_Type> iterator; };
	MemberElement<gie2::CIE_SimulatedImage_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_SimulatedImage> IE_SimulatedImage;
	struct IE_SimulatedImage { typedef Iterator<gie2::CIE_SimulatedImage_Type> iterator; };
	MemberElement<gie2::CIE_SyntheticImage_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_SyntheticImage> IE_SyntheticImage;
	struct IE_SyntheticImage { typedef Iterator<gie2::CIE_SyntheticImage_Type> iterator; };
	MemberElement<gie2::CIE_ThematicGriddedData_Type, _altova_mi_gcv_altova_CCV_Coverage_PropertyType_altova_IE_ThematicGriddedData> IE_ThematicGriddedData;
	struct IE_ThematicGriddedData { typedef Iterator<gie2::CIE_ThematicGriddedData_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_Coverage_PropertyType
