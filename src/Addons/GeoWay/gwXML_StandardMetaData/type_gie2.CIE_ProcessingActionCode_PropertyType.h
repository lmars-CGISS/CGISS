#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ProcessingActionCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ProcessingActionCode_PropertyType



namespace gie
{

namespace gie2
{	

class CIE_ProcessingActionCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CIE_ProcessingActionCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_ProcessingActionCode_PropertyType(CIE_ProcessingActionCode_PropertyType const& init);
	void operator=(CIE_ProcessingActionCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_ProcessingActionCode_PropertyType); }
	MemberElement<gie2::CCodeListValue_Type, _altova_mi_gie2_altova_CIE_ProcessingActionCode_PropertyType_altova_IE_ProcessingActionCode> IE_ProcessingActionCode;
	struct IE_ProcessingActionCode { typedef Iterator<gie2::CCodeListValue_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_ProcessingActionCode_PropertyType
