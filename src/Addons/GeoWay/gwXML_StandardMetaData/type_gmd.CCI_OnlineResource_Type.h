#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_OnlineResource_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_OnlineResource_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CCI_OnlineResource_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCI_OnlineResource_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCI_OnlineResource_Type(CCI_OnlineResource_Type const& init);
	void operator=(CCI_OnlineResource_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CCI_OnlineResource_Type); }
	MemberElement<gmd::CURL_PropertyType, _altova_mi_gmd_altova_CCI_OnlineResource_Type_altova_linkage> linkage;
	struct linkage { typedef Iterator<gmd::CURL_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_OnlineResource_Type_altova_protocol> protocol;
	struct protocol { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_OnlineResource_Type_altova_applicationProfile> applicationProfile;
	struct applicationProfile { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_OnlineResource_Type_altova_name> name;
	struct name { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CCI_OnlineResource_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CCI_OnLineFunctionCode_PropertyType, _altova_mi_gmd_altova_CCI_OnlineResource_Type_altova_function> function;
	struct function { typedef Iterator<gmd::CCI_OnLineFunctionCode_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CCI_OnlineResource_Type
