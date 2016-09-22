#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Constraints_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Constraints_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_Constraints_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_Constraints_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_Constraints_Type(CMD_Constraints_Type const& init);
	void operator=(CMD_Constraints_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_Constraints_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_Constraints_Type_altova_useLimitation> useLimitation;
	struct useLimitation { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Constraints_Type
