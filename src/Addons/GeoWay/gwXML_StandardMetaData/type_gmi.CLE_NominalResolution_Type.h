#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_NominalResolution_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_NominalResolution_Type



namespace gie
{

namespace gmi
{	

class CLE_NominalResolution_Type : public TypeBase
{
public:
	gie_EXPORT CLE_NominalResolution_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_NominalResolution_Type(CLE_NominalResolution_Type const& init);
	void operator=(CLE_NominalResolution_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_NominalResolution_Type); }
	MemberElement<gco::CDistance_PropertyType, _altova_mi_gmi_altova_CLE_NominalResolution_Type_altova_scanningResolution> scanningResolution;
	struct scanningResolution { typedef Iterator<gco::CDistance_PropertyType> iterator; };
	MemberElement<gco::CDistance_PropertyType, _altova_mi_gmi_altova_CLE_NominalResolution_Type_altova_groundResolution> groundResolution;
	struct groundResolution { typedef Iterator<gco::CDistance_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_NominalResolution_Type
