#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_SequenceRule_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_SequenceRule_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CCV_SequenceRule_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CCV_SequenceRule_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CCV_SequenceRule_Type(CCV_SequenceRule_Type const& init);
	void operator=(CCV_SequenceRule_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CCV_SequenceRule_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CCV_SequenceRule_Type_altova_scanDirection> scanDirection;
	struct scanDirection { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CCV_SequenceRule_Type_altova_type> type;
	struct type { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CCV_SequenceRule_Type
