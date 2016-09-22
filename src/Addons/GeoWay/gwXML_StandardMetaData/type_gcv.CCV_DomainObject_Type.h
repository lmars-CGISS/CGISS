#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_DomainObject_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_DomainObject_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CCV_DomainObject_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCV_DomainObject_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_DomainObject_Type(CCV_DomainObject_Type const& init);
	void operator=(CCV_DomainObject_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_DomainObject_Type); }
	MemberElement<gcv::CTM_GeometricPrimitive_PropertyType, _altova_mi_gcv_altova_CCV_DomainObject_Type_altova_temporalElement> temporalElement;
	struct temporalElement { typedef Iterator<gcv::CTM_GeometricPrimitive_PropertyType> iterator; };
	MemberElement<gss::CGM_Object_PropertyType, _altova_mi_gcv_altova_CCV_DomainObject_Type_altova_spatialElement> spatialElement;
	struct spatialElement { typedef Iterator<gss::CGM_Object_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_DomainObject_Type
