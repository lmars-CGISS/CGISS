#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CsecondDefiningParameterType2
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CsecondDefiningParameterType2



namespace gie
{

namespace gie2
{	

class CsecondDefiningParameterType2 : public TypeBase
{
public:
	gie_EXPORT CsecondDefiningParameterType2(xercesc::DOMNode* const& init);
	gie_EXPORT CsecondDefiningParameterType2(CsecondDefiningParameterType2 const& init);
	void operator=(CsecondDefiningParameterType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CsecondDefiningParameterType2); }
	MemberElement<gie2::CSecondDefiningParameterType, _altova_mi_gie2_altova_CsecondDefiningParameterType2_altova_SecondDefiningParameter> SecondDefiningParameter;
	struct SecondDefiningParameter { typedef Iterator<gie2::CSecondDefiningParameterType> iterator; };
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CsecondDefiningParameterType2
