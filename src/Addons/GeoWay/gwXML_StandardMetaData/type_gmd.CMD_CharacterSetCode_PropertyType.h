#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_CharacterSetCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_CharacterSetCode_PropertyType



namespace gie
{

namespace gmd
{	

class CMD_CharacterSetCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMD_CharacterSetCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_CharacterSetCode_PropertyType(CMD_CharacterSetCode_PropertyType const& init);
	void operator=(CMD_CharacterSetCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_CharacterSetCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmd_altova_CMD_CharacterSetCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmd_altova_CMD_CharacterSetCode_PropertyType_altova_MD_CharacterSetCode> MD_CharacterSetCode;
	struct MD_CharacterSetCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_CharacterSetCode_PropertyType
