#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_SensorModel_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_SensorModel_PropertyType



namespace gie
{

namespace gcv
{	

class CSD_SensorModel_PropertyType : public TypeBase
{
public:
	gie_EXPORT CSD_SensorModel_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CSD_SensorModel_PropertyType(CSD_SensorModel_PropertyType const& init);
	void operator=(CSD_SensorModel_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CSD_SensorModel_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gcv::CSD_SensorModel_Type, _altova_mi_gcv_altova_CSD_SensorModel_PropertyType_altova_SD_SensorModel> SD_SensorModel;
	struct SD_SensorModel { typedef Iterator<gcv::CSD_SensorModel_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_SensorModel_PropertyType
