#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_GCPLocation_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_GCPLocation_PropertyType



namespace gie
{

namespace gcv
{	

class CSD_GCPLocation_PropertyType : public TypeBase
{
public:
	gie_EXPORT CSD_GCPLocation_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CSD_GCPLocation_PropertyType(CSD_GCPLocation_PropertyType const& init);
	void operator=(CSD_GCPLocation_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CSD_GCPLocation_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gcv::CSD_GCPLocation_Type, _altova_mi_gcv_altova_CSD_GCPLocation_PropertyType_altova_SD_GCPLocation> SD_GCPLocation;
	struct SD_GCPLocation { typedef Iterator<gcv::CSD_GCPLocation_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_GCPLocation_PropertyType
