#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicDescription_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicDescription_Type

#include "type_gmd.CAbstractEX_GeographicExtent_Type.h"


namespace gie
{

namespace gmd
{	

class CEX_GeographicDescription_Type : public ::gie::gmd::CAbstractEX_GeographicExtent_Type
{
public:
	gie_EXPORT CEX_GeographicDescription_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CEX_GeographicDescription_Type(CEX_GeographicDescription_Type const& init);
	void operator=(CEX_GeographicDescription_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CEX_GeographicDescription_Type); }
	MemberElement<gmd::CMD_Identifier_PropertyType, _altova_mi_gmd_altova_CEX_GeographicDescription_Type_altova_geographicIdentifier> geographicIdentifier;
	struct geographicIdentifier { typedef Iterator<gmd::CMD_Identifier_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CEX_GeographicDescription_Type
