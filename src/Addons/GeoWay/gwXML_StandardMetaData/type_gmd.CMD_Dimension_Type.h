#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Dimension_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Dimension_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_Dimension_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_Dimension_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_Dimension_Type(CMD_Dimension_Type const& init);
	void operator=(CMD_Dimension_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_Dimension_Type); }
	MemberElement<gmd::CMD_DimensionNameTypeCode_PropertyType, _altova_mi_gmd_altova_CMD_Dimension_Type_altova_dimensionName> dimensionName;
	struct dimensionName { typedef Iterator<gmd::CMD_DimensionNameTypeCode_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gmd_altova_CMD_Dimension_Type_altova_dimensionSize> dimensionSize;
	struct dimensionSize { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	MemberElement<gco::CMeasure_PropertyType, _altova_mi_gmd_altova_CMD_Dimension_Type_altova_resolution> resolution;
	struct resolution { typedef Iterator<gco::CMeasure_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_Dimension_Type
