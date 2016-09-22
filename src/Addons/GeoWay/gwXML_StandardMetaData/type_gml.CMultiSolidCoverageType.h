#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidCoverageType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidCoverageType



namespace gie
{

namespace gml
{	

class CMultiSolidCoverageType : public TypeBase
{
public:
	gie_EXPORT CMultiSolidCoverageType(xercesc::DOMNode* const& init);
	gie_EXPORT CMultiSolidCoverageType(CMultiSolidCoverageType const& init);
	void operator=(CMultiSolidCoverageType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMultiSolidCoverageType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CMultiSolidCoverageType_altova_id, 0, 0> id;	// id CID
	MemberElement<gml::CMetaDataPropertyType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_metaDataProperty> metaDataProperty;
	struct metaDataProperty { typedef Iterator<gml::CMetaDataPropertyType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_description> description;
	struct description { typedef Iterator<gml::CStringOrRefType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_descriptionReference> descriptionReference;
	struct descriptionReference { typedef Iterator<gml::CReferenceType> iterator; };
	MemberElement<gml::CCodeWithAuthorityType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_identifier> identifier;
	struct identifier { typedef Iterator<gml::CCodeWithAuthorityType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_name> name;
	struct name { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CBoundingShapeType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_boundedBy> boundedBy;
	struct boundedBy { typedef Iterator<gml::CBoundingShapeType> iterator; };
	MemberElement<gml::CLocationPropertyType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_location> location;
	struct location { typedef Iterator<gml::CLocationPropertyType> iterator; };
	MemberElement<gml::CPriorityLocationPropertyType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_priorityLocation> priorityLocation;
	struct priorityLocation { typedef Iterator<gml::CPriorityLocationPropertyType> iterator; };
	MemberElement<gml::CDomainSetType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_domainSet> domainSet;
	struct domainSet { typedef Iterator<gml::CDomainSetType> iterator; };
	MemberElement<gml::CGridDomainType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_gridDomain> gridDomain;
	struct gridDomain { typedef Iterator<gml::CGridDomainType> iterator; };
	MemberElement<gml::CMultiCurveDomainType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_multiCurveDomain> multiCurveDomain;
	struct multiCurveDomain { typedef Iterator<gml::CMultiCurveDomainType> iterator; };
	MemberElement<gml::CMultiPointDomainType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_multiPointDomain> multiPointDomain;
	struct multiPointDomain { typedef Iterator<gml::CMultiPointDomainType> iterator; };
	MemberElement<gml::CMultiSolidDomainType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_multiSolidDomain> multiSolidDomain;
	struct multiSolidDomain { typedef Iterator<gml::CMultiSolidDomainType> iterator; };
	MemberElement<gml::CMultiSurfaceDomainType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_multiSurfaceDomain> multiSurfaceDomain;
	struct multiSurfaceDomain { typedef Iterator<gml::CMultiSurfaceDomainType> iterator; };
	MemberElement<gml::CRectifiedGridDomainType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_rectifiedGridDomain> rectifiedGridDomain;
	struct rectifiedGridDomain { typedef Iterator<gml::CRectifiedGridDomainType> iterator; };
	MemberElement<gml::CRangeSetType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_rangeSet> rangeSet;
	struct rangeSet { typedef Iterator<gml::CRangeSetType> iterator; };
	MemberElement<gml::CCoverageFunctionType, _altova_mi_gml_altova_CMultiSolidCoverageType_altova_coverageFunction> coverageFunction;
	struct coverageFunction { typedef Iterator<gml::CCoverageFunctionType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMultiSolidCoverageType
