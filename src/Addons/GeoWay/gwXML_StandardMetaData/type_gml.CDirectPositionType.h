#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectPositionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectPositionType

#include "type_gml.CdoubleListType.h"


namespace gie
{

namespace gml
{	

class CDirectPositionType : public ::gie::gml::CdoubleListType
{
public:
	gie_EXPORT CDirectPositionType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectPositionType(CDirectPositionType const& init);
	void operator=(CDirectPositionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectPositionType); }
	gie_EXPORT void operator=(const string_type& value);

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectPositionType_altova_srsName, 0, 0> srsName;	// srsName CanyURI

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CDirectPositionType_altova_srsDimension, 0, 0> srsDimension;	// srsDimension CpositiveInteger

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectPositionType_altova_axisLabels, 0, 0> axisLabels;	// axisLabels CNCNameList

	MemberAttribute<string_type,_altova_mi_gml_altova_CDirectPositionType_altova_uomLabels, 0, 0> uomLabels;	// uomLabels CNCNameList
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectPositionType
