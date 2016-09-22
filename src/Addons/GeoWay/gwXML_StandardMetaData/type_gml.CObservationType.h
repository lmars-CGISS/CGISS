#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CObservationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CObservationType

#include "type_gml.CAbstractFeatureType.h"


namespace gie
{

namespace gml
{	

class CObservationType : public ::gie::gml::CAbstractFeatureType
{
public:
	gie_EXPORT CObservationType(xercesc::DOMNode* const& init);
	gie_EXPORT CObservationType(CObservationType const& init);
	void operator=(CObservationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CObservationType); }
	MemberElement<gml::CTimePrimitivePropertyType, _altova_mi_gml_altova_CObservationType_altova_validTime> validTime;
	struct validTime { typedef Iterator<gml::CTimePrimitivePropertyType> iterator; };
	MemberElement<gml::CProcedurePropertyType, _altova_mi_gml_altova_CObservationType_altova_using2> using2;
	struct using2 { typedef Iterator<gml::CProcedurePropertyType> iterator; };
	MemberElement<gml::CTargetPropertyType, _altova_mi_gml_altova_CObservationType_altova_target> target;
	struct target { typedef Iterator<gml::CTargetPropertyType> iterator; };
	MemberElement<gml::CTargetPropertyType, _altova_mi_gml_altova_CObservationType_altova_subject> subject;
	struct subject { typedef Iterator<gml::CTargetPropertyType> iterator; };
	MemberElement<gml::CResultType, _altova_mi_gml_altova_CObservationType_altova_resultOf> resultOf;
	struct resultOf { typedef Iterator<gml::CResultType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CObservationType
