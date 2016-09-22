#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Date_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Date_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_Date_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_Date_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_Date_Type(CCI_Date_Type const& init);
	void operator=(CCI_Date_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_Date_Type); }
	MemberElement<gco::CDate_PropertyType, _altova_mi_gmd_altova_CCI_Date_Type_altova_date> date;
	struct date { typedef Iterator<gco::CDate_PropertyType> iterator; };
	MemberElement<gmd::CCI_DateTypeCode_PropertyType, _altova_mi_gmd_altova_CCI_Date_Type_altova_dateType> dateType;
	struct dateType { typedef Iterator<gmd::CCI_DateTypeCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_Date_Type
