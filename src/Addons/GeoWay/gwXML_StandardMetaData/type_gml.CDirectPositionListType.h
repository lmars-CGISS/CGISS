#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectPositionListType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectPositionListType

#include "type_gml.CdoubleListType.h"


namespace gie
{

namespace gml
{	

class CDirectPositionListType : public ::gie::gml::CdoubleListType
{
public:
	gie_EXPORT CDirectPositionListType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectPositionListType(CDirectPositionListType const& init);
	void operator=(CDirectPositionListType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectPositionListType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectPositionListType_altova_srsName, 0, 0> srsName;	// srsName CanyURI

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CDirectPositionListType_altova_srsDimension, 0, 0> srsDimension;	// srsDimension CpositiveInteger

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectPositionListType_altova_axisLabels, 0, 0> axisLabels;	// axisLabels CNCNameList

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectPositionListType_altova_uomLabels, 0, 0> uomLabels;	// uomLabels CNCNameList

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CDirectPositionListType_altova_count, 0, 0> count;	// count CpositiveInteger
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectPositionListType
