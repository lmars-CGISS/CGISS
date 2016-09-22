#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CTemporalCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CTemporalCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CTemporalCRSType(CTemporalCRSType const& init);
	void operator=(CTemporalCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTemporalCRSType); }
	MemberElement<gml::CTimeCSPropertyType, _altova_mi_gml_altova_CTemporalCRSType_altova_timeCS> timeCS;
	struct timeCS { typedef Iterator<gml::CTimeCSPropertyType> iterator; };
	MemberElement<gml::CTimeCSPropertyType, _altova_mi_gml_altova_CTemporalCRSType_altova_usesTimeCS> usesTimeCS;
	struct usesTimeCS { typedef Iterator<gml::CTimeCSPropertyType> iterator; };
	MemberElement<gml::CTemporalCSPropertyType, _altova_mi_gml_altova_CTemporalCRSType_altova_usesTemporalCS> usesTemporalCS;
	struct usesTemporalCS { typedef Iterator<gml::CTemporalCSPropertyType> iterator; };
	MemberElement<gml::CTemporalDatumPropertyType, _altova_mi_gml_altova_CTemporalCRSType_altova_temporalDatum> temporalDatum;
	struct temporalDatum { typedef Iterator<gml::CTemporalDatumPropertyType> iterator; };
	MemberElement<gml::CTemporalDatumPropertyType, _altova_mi_gml_altova_CTemporalCRSType_altova_usesTemporalDatum> usesTemporalDatum;
	struct usesTemporalDatum { typedef Iterator<gml::CTemporalDatumPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalCRSType
