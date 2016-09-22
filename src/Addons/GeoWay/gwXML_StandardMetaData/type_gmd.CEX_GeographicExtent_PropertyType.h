#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicExtent_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicExtent_PropertyType



namespace gie
{

namespace gmd
{	

class CEX_GeographicExtent_PropertyType : public TypeBase
{
public:
	gie_EXPORT CEX_GeographicExtent_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CEX_GeographicExtent_PropertyType(CEX_GeographicExtent_PropertyType const& init);
	void operator=(CEX_GeographicExtent_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CEX_GeographicExtent_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmd::CEX_BoundingPolygon_Type, _altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_EX_BoundingPolygon> EX_BoundingPolygon;
	struct EX_BoundingPolygon { typedef Iterator<gmd::CEX_BoundingPolygon_Type> iterator; };
	MemberElement<gmd::CEX_GeographicBoundingBox_Type, _altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_EX_GeographicBoundingBox> EX_GeographicBoundingBox;
	struct EX_GeographicBoundingBox { typedef Iterator<gmd::CEX_GeographicBoundingBox_Type> iterator; };
	MemberElement<gmd::CEX_GeographicDescription_Type, _altova_mi_gmd_altova_CEX_GeographicExtent_PropertyType_altova_EX_GeographicDescription> EX_GeographicDescription;
	struct EX_GeographicDescription { typedef Iterator<gmd::CEX_GeographicDescription_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicExtent_PropertyType
