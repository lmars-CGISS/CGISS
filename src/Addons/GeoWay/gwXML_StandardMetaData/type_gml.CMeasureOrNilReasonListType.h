#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureOrNilReasonListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureOrNilReasonListType

#include "type_gml.CdoubleOrNilReasonListType.h"


namespace gie
{

namespace gml
{	

class CMeasureOrNilReasonListType : public ::gie::gml::CdoubleOrNilReasonListType
{
public:
	gie_EXPORT CMeasureOrNilReasonListType(xercesc::DOMNode* const& init);
	gie_EXPORT CMeasureOrNilReasonListType(CMeasureOrNilReasonListType const& init);
	void operator=(CMeasureOrNilReasonListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMeasureOrNilReasonListType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CMeasureOrNilReasonListType_altova_uom, 0, 0> uom;	// uom CUomIdentifier
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureOrNilReasonListType
