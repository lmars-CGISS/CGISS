#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTriangulatedSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTriangulatedSurfaceType



namespace gie
{

namespace gml
{	

class CTriangulatedSurfaceType : public TypeBase
{
public:
	gie_EXPORT CTriangulatedSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CTriangulatedSurfaceType(CTriangulatedSurfaceType const& init);
	void operator=(CTriangulatedSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTriangulatedSurfaceType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CTriangulatedSurfaceType_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_gml_altova_CTriangulatedSurfaceType_altova_srsName, 0, 0> srsName;	// srsName CanyURI

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CTriangulatedSurfaceType_altova_srsDimension, 0, 0> srsDimension;	// srsDimension CpositiveInteger

	MemberAttribute<string_type,_altova_mi_gml_altova_CTriangulatedSurfaceType_altova_axisLabels, 0, 0> axisLabels;	// axisLabels CNCNameList

	MemberAttribute<string_type,_altova_mi_gml_altova_CTriangulatedSurfaceType_altova_uomLabels, 0, 0> uomLabels;	// uomLabels CNCNameList
	MemberElement<gml::CMetaDataPropertyType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_metaDataProperty> metaDataProperty;
	struct metaDataProperty { typedef Iterator<gml::CMetaDataPropertyType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_description> description;
	struct description { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_descriptionReference> descriptionReference;
	struct descriptionReference { typedef Iterator<gml::CReferenceType> iterator; };
	MemberElement<gml::CCodeWithAuthorityType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_identifier> identifier;
	struct identifier { typedef Iterator<gml::CCodeWithAuthorityType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_name> name;
	struct name { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CSurfacePatchArrayPropertyType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_patches> patches;
	struct patches { typedef Iterator<gml::CSurfacePatchArrayPropertyType> iterator; };
	MemberElement<gml::CPolygonPatchArrayPropertyType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_polygonPatches> polygonPatches;
	struct polygonPatches { typedef Iterator<gml::CPolygonPatchArrayPropertyType> iterator; };
	MemberElement<gml::CTrianglePatchArrayPropertyType, _altova_mi_gml_altova_CTriangulatedSurfaceType_altova_trianglePatches> trianglePatches;
	struct trianglePatches { typedef Iterator<gml::CTrianglePatchArrayPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTriangulatedSurfaceType
