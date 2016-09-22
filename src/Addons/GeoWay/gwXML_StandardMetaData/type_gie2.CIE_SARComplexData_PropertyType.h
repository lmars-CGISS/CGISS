#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARComplexData_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARComplexData_PropertyType



namespace gie
{

namespace gie2
{	

class CIE_SARComplexData_PropertyType : public TypeBase
{
public:
	gie_EXPORT CIE_SARComplexData_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_SARComplexData_PropertyType(CIE_SARComplexData_PropertyType const& init);
	void operator=(CIE_SARComplexData_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_SARComplexData_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gie2_altova_CIE_SARComplexData_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gie2::CIE_SARComplexData_Type, _altova_mi_gie2_altova_CIE_SARComplexData_PropertyType_altova_IE_SARComplexData> IE_SARComplexData;
	struct IE_SARComplexData { typedef Iterator<gie2::CIE_SARComplexData_Type> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_SARComplexData_PropertyType
