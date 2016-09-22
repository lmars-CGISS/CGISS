#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSingleCRSPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSingleCRSPropertyType



namespace gie
{

namespace gml
{	

class CSingleCRSPropertyType : public TypeBase
{
public:
	gie_EXPORT CSingleCRSPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CSingleCRSPropertyType(CSingleCRSPropertyType const& init);
	void operator=(CSingleCRSPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSingleCRSPropertyType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CSingleCRSPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CDerivedCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_DerivedCRS> DerivedCRS;
	struct DerivedCRS { typedef Iterator<gml::CDerivedCRSType> iterator; };
	MemberElement<gml::CEngineeringCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_EngineeringCRS> EngineeringCRS;
	struct EngineeringCRS { typedef Iterator<gml::CEngineeringCRSType> iterator; };
	MemberElement<gml::CGeocentricCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_GeocentricCRS> GeocentricCRS;
	struct GeocentricCRS { typedef Iterator<gml::CGeocentricCRSType> iterator; };
	MemberElement<gml::CGeodeticCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_GeodeticCRS> GeodeticCRS;
	struct GeodeticCRS { typedef Iterator<gml::CGeodeticCRSType> iterator; };
	MemberElement<gml::CGeographicCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_GeographicCRS> GeographicCRS;
	struct GeographicCRS { typedef Iterator<gml::CGeographicCRSType> iterator; };
	MemberElement<gml::CImageCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_ImageCRS> ImageCRS;
	struct ImageCRS { typedef Iterator<gml::CImageCRSType> iterator; };
	MemberElement<gml::CProjectedCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_ProjectedCRS> ProjectedCRS;
	struct ProjectedCRS { typedef Iterator<gml::CProjectedCRSType> iterator; };
	MemberElement<gml::CTemporalCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_TemporalCRS> TemporalCRS;
	struct TemporalCRS { typedef Iterator<gml::CTemporalCRSType> iterator; };
	MemberElement<gml::CVerticalCRSType, _altova_mi_gml_altova_CSingleCRSPropertyType_altova_VerticalCRS> VerticalCRS;
	struct VerticalCRS { typedef Iterator<gml::CVerticalCRSType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSingleCRSPropertyType
