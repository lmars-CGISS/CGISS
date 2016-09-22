#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoverageType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoverageType

#include "type_gml.CAbstractFeatureType.h"


namespace gie
{

namespace gml
{	

class CAbstractCoverageType : public ::gie::gml::CAbstractFeatureType
{
public:
	gie_EXPORT CAbstractCoverageType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractCoverageType(CAbstractCoverageType const& init);
	void operator=(CAbstractCoverageType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractCoverageType); }
	MemberElement<gml::CDomainSetType, _altova_mi_gml_altova_CAbstractCoverageType_altova_domainSet> domainSet;
	struct domainSet { typedef Iterator<gml::CDomainSetType> iterator; };
	MemberElement<gml::CGridDomainType, _altova_mi_gml_altova_CAbstractCoverageType_altova_gridDomain> gridDomain;
	struct gridDomain { typedef Iterator<gml::CGridDomainType> iterator; };
	MemberElement<gml::CMultiCurveDomainType, _altova_mi_gml_altova_CAbstractCoverageType_altova_multiCurveDomain> multiCurveDomain;
	struct multiCurveDomain { typedef Iterator<gml::CMultiCurveDomainType> iterator; };
	MemberElement<gml::CMultiPointDomainType, _altova_mi_gml_altova_CAbstractCoverageType_altova_multiPointDomain> multiPointDomain;
	struct multiPointDomain { typedef Iterator<gml::CMultiPointDomainType> iterator; };
	MemberElement<gml::CMultiSolidDomainType, _altova_mi_gml_altova_CAbstractCoverageType_altova_multiSolidDomain> multiSolidDomain;
	struct multiSolidDomain { typedef Iterator<gml::CMultiSolidDomainType> iterator; };
	MemberElement<gml::CMultiSurfaceDomainType, _altova_mi_gml_altova_CAbstractCoverageType_altova_multiSurfaceDomain> multiSurfaceDomain;
	struct multiSurfaceDomain { typedef Iterator<gml::CMultiSurfaceDomainType> iterator; };
	MemberElement<gml::CRectifiedGridDomainType, _altova_mi_gml_altova_CAbstractCoverageType_altova_rectifiedGridDomain> rectifiedGridDomain;
	struct rectifiedGridDomain { typedef Iterator<gml::CRectifiedGridDomainType> iterator; };
	MemberElement<gml::CRangeSetType, _altova_mi_gml_altova_CAbstractCoverageType_altova_rangeSet> rangeSet;
	struct rangeSet { typedef Iterator<gml::CRangeSetType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCoverageType
