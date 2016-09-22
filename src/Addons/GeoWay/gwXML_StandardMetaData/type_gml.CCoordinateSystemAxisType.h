#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoordinateSystemAxisType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoordinateSystemAxisType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CCoordinateSystemAxisType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CCoordinateSystemAxisType(xercesc::DOMNode* const& init);
	gie_EXPORT CCoordinateSystemAxisType(CCoordinateSystemAxisType const& init);
	void operator=(CCoordinateSystemAxisType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCoordinateSystemAxisType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CCoordinateSystemAxisType_altova_uom, 0, 0> uom;	// uom CanyURI
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CCoordinateSystemAxisType_altova_axisAbbrev> axisAbbrev;
	struct axisAbbrev { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<gml::CCodeWithAuthorityType, _altova_mi_gml_altova_CCoordinateSystemAxisType_altova_axisDirection> axisDirection;
	struct axisDirection { typedef Iterator<gml::CCodeWithAuthorityType> iterator; };
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CCoordinateSystemAxisType_altova_minimumValue> minimumValue;
	struct minimumValue { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CCoordinateSystemAxisType_altova_maximumValue> maximumValue;
	struct maximumValue { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<gml::CCodeWithAuthorityType, _altova_mi_gml_altova_CCoordinateSystemAxisType_altova_rangeMeaning> rangeMeaning;
	struct rangeMeaning { typedef Iterator<gml::CCodeWithAuthorityType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCoordinateSystemAxisType
