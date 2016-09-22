#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_CategoricalGriddedData_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_CategoricalGriddedData_Type

#include "type_gie2.CIE_ThematicGriddedData_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_CategoricalGriddedData_Type : public ::gie::gie2::CIE_ThematicGriddedData_Type
{
public:
	gie_EXPORT CIE_CategoricalGriddedData_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_CategoricalGriddedData_Type(CIE_CategoricalGriddedData_Type const& init);
	void operator=(CIE_CategoricalGriddedData_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_CategoricalGriddedData_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalGriddedData_Type_altova_classificationDescription> classificationDescription;
	struct classificationDescription { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalGriddedData_Type_altova_numberOfCategories> numberOfCategories;
	struct numberOfCategories { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalGriddedData_Type_altova_bitsPerValue> bitsPerValue;
	struct bitsPerValue { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gie2::CIE_CategoricalValueAndColour_PropertyType, _altova_mi_gie2_altova_CIE_CategoricalGriddedData_Type_altova_lookupTable> lookupTable;
	struct lookupTable { typedef Iterator<gie2::CIE_CategoricalValueAndColour_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_CategoricalGriddedData_Type
