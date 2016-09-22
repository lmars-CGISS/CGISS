#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Storage_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Storage_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_Storage_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_Storage_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_Storage_Type(CIE_Storage_Type const& init);
	void operator=(CIE_Storage_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_Storage_Type); }
	MemberElement<gmd::CMD_Format_PropertyType, _altova_mi_gie2_altova_CIE_Storage_Type_altova_format> format;
	struct format { typedef Iterator<gmd::CMD_Format_PropertyType> iterator; };
	MemberElement<gie2::CIE_LayerSequenceCode_PropertyType, _altova_mi_gie2_altova_CIE_Storage_Type_altova_layerSequence> layerSequence;
	struct layerSequence { typedef Iterator<gie2::CIE_LayerSequenceCode_PropertyType> iterator; };
	MemberElement<gcv::CCV_SequenceRule_PropertyType, _altova_mi_gie2_altova_CIE_Storage_Type_altova_spatialSequence> spatialSequence;
	struct spatialSequence { typedef Iterator<gcv::CCV_SequenceRule_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_Storage_Type
