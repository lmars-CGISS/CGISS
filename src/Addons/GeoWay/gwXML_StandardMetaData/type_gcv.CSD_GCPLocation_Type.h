#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_GCPLocation_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_GCPLocation_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CSD_GCPLocation_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CSD_GCPLocation_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CSD_GCPLocation_Type(CSD_GCPLocation_Type const& init);
	void operator=(CSD_GCPLocation_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CSD_GCPLocation_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CSD_GCPLocation_Type_altova_locationGridPosition> locationGridPosition;
	struct locationGridPosition { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CSD_GCPLocation_Type_altova_locationGeographicPosition> locationGeographicPosition;
	struct locationGeographicPosition { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_GCPLocation_Type
