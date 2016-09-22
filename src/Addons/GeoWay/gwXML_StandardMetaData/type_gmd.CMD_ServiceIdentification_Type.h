#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ServiceIdentification_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ServiceIdentification_Type

#include "type_gmd.CAbstractMD_Identification_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_ServiceIdentification_Type : public ::gie::gmd::CAbstractMD_Identification_Type
{
public:
	gie_EXPORT CMD_ServiceIdentification_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_ServiceIdentification_Type(CMD_ServiceIdentification_Type const& init);
	void operator=(CMD_ServiceIdentification_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_ServiceIdentification_Type); }
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ServiceIdentification_Type
