#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBoundedFeatureType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBoundedFeatureType



namespace gie
{

namespace gml
{	

class CBoundedFeatureType : public TypeBase
{
public:
	gie_EXPORT CBoundedFeatureType(xercesc::DOMNode* const& init);
	gie_EXPORT CBoundedFeatureType(CBoundedFeatureType const& init);
	void operator=(CBoundedFeatureType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CBoundedFeatureType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CBoundedFeatureType_altova_id, 0, 0> id;	// id CID
	MemberElement<gml::CMetaDataPropertyType, _altova_mi_gml_altova_CBoundedFeatureType_altova_metaDataProperty> metaDataProperty;
	struct metaDataProperty { typedef Iterator<gml::CMetaDataPropertyType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CBoundedFeatureType_altova_description> description;
	struct description { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CBoundedFeatureType_altova_descriptionReference> descriptionReference;
	struct descriptionReference { typedef Iterator<gml::CReferenceType> iterator; };
	MemberElement<gml::CCodeWithAuthorityType, _altova_mi_gml_altova_CBoundedFeatureType_altova_identifier> identifier;
	struct identifier { typedef Iterator<gml::CCodeWithAuthorityType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CBoundedFeatureType_altova_name> name;
	struct name { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CBoundingShapeType, _altova_mi_gml_altova_CBoundedFeatureType_altova_boundedBy> boundedBy;
	struct boundedBy { typedef Iterator<gml::CBoundingShapeType> iterator; };
	MemberElement<gml::CLocationPropertyType, _altova_mi_gml_altova_CBoundedFeatureType_altova_location> location;
	struct location { typedef Iterator<gml::CLocationPropertyType> iterator; };
	MemberElement<gml::CPriorityLocationPropertyType, _altova_mi_gml_altova_CBoundedFeatureType_altova_priorityLocation> priorityLocation;
	struct priorityLocation { typedef Iterator<gml::CPriorityLocationPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBoundedFeatureType
