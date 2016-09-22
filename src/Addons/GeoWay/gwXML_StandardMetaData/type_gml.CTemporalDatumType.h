#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalDatumType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalDatumType

#include "type_gml.CTemporalDatumBaseType.h"


namespace gie
{

namespace gml
{	

class CTemporalDatumType : public ::gie::gml::CTemporalDatumBaseType
{
public:
	gie_EXPORT CTemporalDatumType(xercesc::DOMNode* const& init);
	gie_EXPORT CTemporalDatumType(CTemporalDatumType const& init);
	void operator=(CTemporalDatumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTemporalDatumType); }
	MemberElement<xs::CdateTimeType, _altova_mi_gml_altova_CTemporalDatumType_altova_origin> origin;
	struct origin { typedef Iterator<xs::CdateTimeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTemporalDatumType
