#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLanguageCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLanguageCode_PropertyType



namespace gie
{

namespace gmd
{	

class CLanguageCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CLanguageCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLanguageCode_PropertyType(CLanguageCode_PropertyType const& init);
	void operator=(CLanguageCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CLanguageCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmd_altova_CLanguageCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmd_altova_CLanguageCode_PropertyType_altova_LanguageCode> LanguageCode;
	struct LanguageCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CLanguageCode_PropertyType
