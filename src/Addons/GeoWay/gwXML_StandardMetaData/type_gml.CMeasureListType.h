#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureListType

#include "type_gml.CdoubleListType.h"


namespace gie
{

namespace gml
{	

class CMeasureListType : public ::gie::gml::CdoubleListType
{
public:
	gie_EXPORT CMeasureListType(xercesc::DOMNode* const& init);
	gie_EXPORT CMeasureListType(CMeasureListType const& init);
	void operator=(CMeasureListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CMeasureListType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CMeasureListType_altova_uom, 0, 0> uom;	// uom CUomIdentifier
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CMeasureListType
