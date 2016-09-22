#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometryType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometryType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CAbstractGeometryType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CAbstractGeometryType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeometryType(CAbstractGeometryType const& init);
	void operator=(CAbstractGeometryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeometryType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractGeometryType_altova_srsName, 0, 0> srsName;	// srsName CanyURI

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CAbstractGeometryType_altova_srsDimension, 0, 0> srsDimension;	// srsDimension CpositiveInteger

	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractGeometryType_altova_axisLabels, 0, 0> axisLabels;	// axisLabels CNCNameList

	MemberAttribute<string_type,_altova_mi_gml_altova_CAbstractGeometryType_altova_uomLabels, 0, 0> uomLabels;	// uomLabels CNCNameList
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeometryType
