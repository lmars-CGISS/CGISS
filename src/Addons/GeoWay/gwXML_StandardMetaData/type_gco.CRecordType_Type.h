#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CRecordType_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CRecordType_Type

#include "type_xs.CstringType.h"


namespace gie
{

namespace gco
{	

class CRecordType_Type : public ::gie::xs::CstringType
{
public:
	gie_EXPORT CRecordType_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CRecordType_Type(CRecordType_Type const& init);
	void operator=(CRecordType_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CRecordType_Type); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gco_altova_CRecordType_Type_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CRecordType_Type
