#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureType

#include "type_xs.CdoubleType.h"


namespace gie
{

namespace gml
{	

class CMeasureType : public ::gie::xs::CdoubleType
{
public:
	gie_EXPORT CMeasureType(xercesc::DOMNode* const& init);
	gie_EXPORT CMeasureType(CMeasureType const& init);
	void operator=(CMeasureType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMeasureType); }
	gie_EXPORT void operator=(const double& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CMeasureType_altova_uom, 0, 0> uom;	// uom CUomIdentifier
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureType
