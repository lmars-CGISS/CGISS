#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CUomAngle_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CUomAngle_PropertyType



namespace gie
{

namespace gco
{	

class CUomAngle_PropertyType : public TypeBase
{
public:
	gie_EXPORT CUomAngle_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CUomAngle_PropertyType(CUomAngle_PropertyType const& init);
	void operator=(CUomAngle_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CUomAngle_PropertyType); }

	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType

	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_uuidref, 0, 0> uuidref;	// uuidref Cstring
	MemberAttribute<string_type,_altova_mi_gco_altova_CUomAngle_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CUnitDefinitionType, _altova_mi_gco_altova_CUomAngle_PropertyType_altova_UnitDefinition> UnitDefinition;
	struct UnitDefinition { typedef Iterator<gml::CUnitDefinitionType> iterator; };
	MemberElement<gml::CBaseUnitType, _altova_mi_gco_altova_CUomAngle_PropertyType_altova_BaseUnit> BaseUnit;
	struct BaseUnit { typedef Iterator<gml::CBaseUnitType> iterator; };
	MemberElement<gml::CConventionalUnitType, _altova_mi_gco_altova_CUomAngle_PropertyType_altova_ConventionalUnit> ConventionalUnit;
	struct ConventionalUnit { typedef Iterator<gml::CConventionalUnitType> iterator; };
	MemberElement<gml::CDerivedUnitType, _altova_mi_gco_altova_CUomAngle_PropertyType_altova_DerivedUnit> DerivedUnit;
	struct DerivedUnit { typedef Iterator<gml::CDerivedUnitType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CUomAngle_PropertyType
