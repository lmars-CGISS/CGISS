#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimePrimitiveType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimePrimitiveType

#include "type_gml.CAbstractTimeObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractTimePrimitiveType : public ::gie::gml::CAbstractTimeObjectType
{
public:
	gie_EXPORT CAbstractTimePrimitiveType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractTimePrimitiveType(CAbstractTimePrimitiveType const& init);
	void operator=(CAbstractTimePrimitiveType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractTimePrimitiveType); }
	MemberElement<gml::CRelatedTimeType, _altova_mi_gml_altova_CAbstractTimePrimitiveType_altova_relatedTime> relatedTime;
	struct relatedTime { typedef Iterator<gml::CRelatedTimeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractTimePrimitiveType
