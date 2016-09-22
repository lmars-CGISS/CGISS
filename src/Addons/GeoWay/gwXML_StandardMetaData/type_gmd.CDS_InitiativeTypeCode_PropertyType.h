#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_InitiativeTypeCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_InitiativeTypeCode_PropertyType



namespace gie
{

namespace gmd
{	

class CDS_InitiativeTypeCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CDS_InitiativeTypeCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CDS_InitiativeTypeCode_PropertyType(CDS_InitiativeTypeCode_PropertyType const& init);
	void operator=(CDS_InitiativeTypeCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CDS_InitiativeTypeCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmd_altova_CDS_InitiativeTypeCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmd_altova_CDS_InitiativeTypeCode_PropertyType_altova_DS_InitiativeTypeCode> DS_InitiativeTypeCode;
	struct DS_InitiativeTypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CDS_InitiativeTypeCode_PropertyType
