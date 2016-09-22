#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_Sensor_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_Sensor_PropertyType



namespace gie
{

namespace gmd
{	

class CDS_Sensor_PropertyType : public TypeBase
{
public:
	gie_EXPORT CDS_Sensor_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDS_Sensor_PropertyType(CDS_Sensor_PropertyType const& init);
	void operator=(CDS_Sensor_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDS_Sensor_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmd::CDS_Sensor_Type, _altova_mi_gmd_altova_CDS_Sensor_PropertyType_altova_DS_Sensor> DS_Sensor;
	struct DS_Sensor { typedef Iterator<gmd::CDS_Sensor_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_Sensor_PropertyType
