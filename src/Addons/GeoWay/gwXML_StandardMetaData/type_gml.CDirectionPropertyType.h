#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectionPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectionPropertyType



namespace gie
{

namespace gml
{	

class CDirectionPropertyType : public TypeBase
{
public:
	gie_EXPORT CDirectionPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectionPropertyType(CDirectionPropertyType const& init);
	void operator=(CDirectionPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectionPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CDirectionPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectionPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CDirectionVectorType, _altova_mi_gml_altova_CDirectionPropertyType_altova_DirectionVector> DirectionVector;
	struct DirectionVector { typedef Iterator<gml::CDirectionVectorType> iterator; };
	MemberElement<gml::CDirectionDescriptionType, _altova_mi_gml_altova_CDirectionPropertyType_altova_DirectionDescription> DirectionDescription;
	struct DirectionDescription { typedef Iterator<gml::CDirectionDescriptionType> iterator; };
	MemberElement<gml::CCompassPointEnumerationType, _altova_mi_gml_altova_CDirectionPropertyType_altova_CompassPoint> CompassPoint;
	struct CompassPoint { typedef Iterator<gml::CCompassPointEnumerationType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CDirectionPropertyType_altova_DirectionKeyword> DirectionKeyword;
	struct DirectionKeyword { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CDirectionPropertyType_altova_DirectionString> DirectionString;
	struct DirectionString { typedef Iterator<gml::CStringOrRefType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectionPropertyType
