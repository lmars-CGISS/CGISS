#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DatatypeCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DatatypeCode_PropertyType



namespace gie
{

namespace gmd
{	

class CMD_DatatypeCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMD_DatatypeCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_DatatypeCode_PropertyType(CMD_DatatypeCode_PropertyType const& init);
	void operator=(CMD_DatatypeCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_DatatypeCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmd_altova_CMD_DatatypeCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gco::CCodeListValue_Type, _altova_mi_gmd_altova_CMD_DatatypeCode_PropertyType_altova_MD_DatatypeCode> MD_DatatypeCode;
	struct MD_DatatypeCode { typedef Iterator<gco::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_DatatypeCode_PropertyType
