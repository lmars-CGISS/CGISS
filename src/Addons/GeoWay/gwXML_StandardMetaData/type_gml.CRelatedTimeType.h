#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRelatedTimeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRelatedTimeType

#include "type_gml.CTimePrimitivePropertyType.h"


namespace gie
{

namespace gml
{	

class CRelatedTimeType : public ::gie::gml::CTimePrimitivePropertyType
{
public:
	gie_EXPORT CRelatedTimeType(xercesc::DOMNode* const& init);
	gie_EXPORT CRelatedTimeType(CRelatedTimeType const& init);
	void operator=(CRelatedTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRelatedTimeType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CRelatedTimeType_altova_relativePosition, 0, 13> relativePosition;	// relativePosition CrelativePositionType
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRelatedTimeType
