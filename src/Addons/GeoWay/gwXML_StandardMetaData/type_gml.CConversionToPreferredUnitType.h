#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConversionToPreferredUnitType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConversionToPreferredUnitType

#include "type_gml.CUnitOfMeasureType.h"


namespace gie
{

namespace gml
{	

class CConversionToPreferredUnitType : public ::gie::gml::CUnitOfMeasureType
{
public:
	gie_EXPORT CConversionToPreferredUnitType(xercesc::DOMNode* const& init);
	gie_EXPORT CConversionToPreferredUnitType(CConversionToPreferredUnitType const& init);
	void operator=(CConversionToPreferredUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CConversionToPreferredUnitType); }
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CConversionToPreferredUnitType_altova_factor> factor;
	struct factor { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<gml::CFormulaType, _altova_mi_gml_altova_CConversionToPreferredUnitType_altova_formula> formula;
	struct formula { typedef Iterator<gml::CFormulaType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConversionToPreferredUnitType
