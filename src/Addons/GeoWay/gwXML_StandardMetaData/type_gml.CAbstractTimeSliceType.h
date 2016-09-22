#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeSliceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeSliceType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CAbstractTimeSliceType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CAbstractTimeSliceType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTimeSliceType(CAbstractTimeSliceType const& init);
	void operator=(CAbstractTimeSliceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTimeSliceType); }
	MemberElement<gml::CTimePrimitivePropertyType, _altova_mi_gml_altova_CAbstractTimeSliceType_altova_validTime> validTime;
	struct validTime { typedef Iterator<gml::CTimePrimitivePropertyType> iterator; };
	MemberElement<gml::CStringOrRefType, _altova_mi_gml_altova_CAbstractTimeSliceType_altova_dataSource> dataSource;
	struct dataSource { typedef Iterator<gml::CStringOrRefType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimeSliceType
