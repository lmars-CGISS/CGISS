#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_ImageIdentifiableGCP_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_ImageIdentifiableGCP_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CSD_ImageIdentifiableGCP_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CSD_ImageIdentifiableGCP_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CSD_ImageIdentifiableGCP_Type(CSD_ImageIdentifiableGCP_Type const& init);
	void operator=(CSD_ImageIdentifiableGCP_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CSD_ImageIdentifiableGCP_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CSD_ImageIdentifiableGCP_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_ImageIdentifiableGCP_Type
