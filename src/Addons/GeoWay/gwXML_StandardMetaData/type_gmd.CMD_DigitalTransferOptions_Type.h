#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DigitalTransferOptions_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DigitalTransferOptions_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_DigitalTransferOptions_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_DigitalTransferOptions_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_DigitalTransferOptions_Type(CMD_DigitalTransferOptions_Type const& init);
	void operator=(CMD_DigitalTransferOptions_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_DigitalTransferOptions_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CMD_DigitalTransferOptions_Type_altova_unitsOfDistribution> unitsOfDistribution;
	struct unitsOfDistribution { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gmd_altova_CMD_DigitalTransferOptions_Type_altova_transferSize> transferSize;
	struct transferSize { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gmd::CCI_OnlineResource_PropertyType, _altova_mi_gmd_altova_CMD_DigitalTransferOptions_Type_altova_onLine> onLine;
	struct onLine { typedef Iterator<gmd::CCI_OnlineResource_PropertyType> iterator; };
	MemberElement<gmd::CMD_Medium_PropertyType, _altova_mi_gmd_altova_CMD_DigitalTransferOptions_Type_altova_offLine> offLine;
	struct offLine { typedef Iterator<gmd::CMD_Medium_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DigitalTransferOptions_Type
