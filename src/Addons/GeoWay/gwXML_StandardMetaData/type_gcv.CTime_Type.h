#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTime_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTime_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CTime_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CTime_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CTime_Type(CTime_Type const& init);
	void operator=(CTime_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CTime_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CTime_Type_altova_hour> hour;
	struct hour { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CTime_Type_altova_minute> minute;
	struct minute { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CTime_Type_altova_second> second;
	struct second { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CTime_Type_altova_timeZone> timeZone;
	struct timeZone { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CTime_Type
