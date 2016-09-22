#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMemberName_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMemberName_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gco
{	

class CMemberName_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMemberName_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMemberName_Type(CMemberName_Type const& init);
	void operator=(CMemberName_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CMemberName_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gco_altova_CMemberName_Type_altova_aName> aName;
	struct aName { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CTypeName_PropertyType, _altova_mi_gco_altova_CMemberName_Type_altova_attributeType> attributeType;
	struct attributeType { typedef Iterator<gco::CTypeName_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CMemberName_Type
