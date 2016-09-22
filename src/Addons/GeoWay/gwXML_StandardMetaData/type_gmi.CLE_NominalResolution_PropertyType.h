#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_NominalResolution_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_NominalResolution_PropertyType



namespace gie
{

namespace gmi
{	

class CLE_NominalResolution_PropertyType : public TypeBase
{
public:
	gie_EXPORT CLE_NominalResolution_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLE_NominalResolution_PropertyType(CLE_NominalResolution_PropertyType const& init);
	void operator=(CLE_NominalResolution_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CLE_NominalResolution_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmi_altova_CLE_NominalResolution_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmi::CLE_NominalResolution_Type, _altova_mi_gmi_altova_CLE_NominalResolution_PropertyType_altova_LE_NominalResolution> LE_NominalResolution;
	struct LE_NominalResolution { typedef Iterator<gmi::CLE_NominalResolution_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CLE_NominalResolution_PropertyType
