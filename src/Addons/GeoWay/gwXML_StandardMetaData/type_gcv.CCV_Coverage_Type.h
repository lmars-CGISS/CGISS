#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_Coverage_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_Coverage_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CCV_Coverage_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCV_Coverage_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_Coverage_Type(CCV_Coverage_Type const& init);
	void operator=(CCV_Coverage_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_Coverage_Type); }
	MemberElement<gcv::CCV_CommonPointRule_PropertyType, _altova_mi_gcv_altova_CCV_Coverage_Type_altova_commonPointRule> commonPointRule;
	struct commonPointRule { typedef Iterator<gcv::CCV_CommonPointRule_PropertyType> iterator; };
	MemberElement<gmd::CEX_Extent_PropertyType, _altova_mi_gcv_altova_CCV_Coverage_Type_altova_domainExtent> domainExtent;
	struct domainExtent { typedef Iterator<gmd::CEX_Extent_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CCV_Coverage_Type_altova_rangeType> rangeType;
	struct rangeType { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gcv::CCV_DomainObject_PropertyType, _altova_mi_gcv_altova_CCV_Coverage_Type_altova_domainElement> domainElement;
	struct domainElement { typedef Iterator<gcv::CCV_DomainObject_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CCV_Coverage_Type_altova_rangeElement> rangeElement;
	struct rangeElement { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gsr::CSC_CRS_PropertyType, _altova_mi_gcv_altova_CCV_Coverage_Type_altova_CRS> CRS;
	struct CRS { typedef Iterator<gsr::CSC_CRS_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_Coverage_Type
