#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeCalendarType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeCalendarType

#include "type_gml.CTimeReferenceSystemType.h"


namespace gie
{

namespace gml
{	

class CTimeCalendarType : public ::gie::gml::CTimeReferenceSystemType
{
public:
	gie_EXPORT CTimeCalendarType(xercesc::DOMNode* const& init);
	gie_EXPORT CTimeCalendarType(CTimeCalendarType const& init);
	void operator=(CTimeCalendarType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTimeCalendarType); }
	MemberElement<gml::CTimeCalendarEraPropertyType, _altova_mi_gml_altova_CTimeCalendarType_altova_referenceFrame> referenceFrame;
	struct referenceFrame { typedef Iterator<gml::CTimeCalendarEraPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTimeCalendarType
