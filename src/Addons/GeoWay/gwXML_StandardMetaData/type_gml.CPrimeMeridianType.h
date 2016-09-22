#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPrimeMeridianType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPrimeMeridianType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CPrimeMeridianType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CPrimeMeridianType(xercesc::DOMNode* const& init);
	gie_EXPORT CPrimeMeridianType(CPrimeMeridianType const& init);
	void operator=(CPrimeMeridianType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPrimeMeridianType); }
	MemberElement<gml::CAngleType, _altova_mi_gml_altova_CPrimeMeridianType_altova_greenwichLongitude> greenwichLongitude;
	struct greenwichLongitude { typedef Iterator<gml::CAngleType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPrimeMeridianType
